// Example : neural network learning
// usage: prog training_data_file testing_data_file

// For use with test / training datasets : handwritten_ex

// Author : Toby Breckon, toby.breckon@cranfield.ac.uk

// Copyright (c) 2010 School of Engineering, Cranfield University
// License : LGPL - http://www.gnu.org/licenses/lgpl.html

#include "cv.h"       // opencv general include file
#include "ml.h"     // opencv machine learning include file

#include <stdio.h>

// N.B. classes are integer handwritten digits in range 0-9

/******************************************************************************/

// loads the sample database from file (which is a CSV text file)

int read_data_from_csv(const char* filename, CvMat* data, CvMat* classes,
             int n_samples )
{

  int classlabel; // the class label

  // if we can't read the input file then return 0
    FILE* f = fopen( filename, "r" );
  if( !f )
  {
    printf("ERROR: cannot read file %s\n",  filename);
    return 0; // all not OK
  }

  // for each sample in the file

  for(int line = 0; line < n_samples; line++)
    {
    // for each attribute on the line in the file

    for(int attribute = 0; attribute < (attributes_per_sample + 1); attribute++)
      {
      if (attribute < attributes_per_sample)
        {
        // first 256 elements (0-255) in each line are the attributes
        fscanf(f, "%f,", &(CV_MAT_ELEM(*data, float, line, attribute)));
        // printf("%f,", CV_MAT_ELEM(*data, float, line, attribute));
        }
      else if (attribute == attributes_per_sample)
        {
        // attribute 256 is the class label {0 ... 9}
        fscanf(f, "%i,", &classlabel);
        CV_MAT_ELEM(*classes, float, line, classlabel) = 1.0;
        // printf("%f\n", CV_MAT_ELEM(*classes, float, line, classlabel));
        }
      }
    }

  fclose(f);

  return 1; // all OK
}

/******************************************************************************/

int main( int argc, char** argv )
{
  int number_of_training_samples = 797;
  int attributes_per_sample = 256;
  int number_of_testing_samples = 796;

  int number_of_classes = 10;

  // define training data storage matrices (one for attribute examples, one
  // for classifications)

  CvMat* training_data = cvCreateMat(number_of_training_samples, attributes_per_sample, CV_32FC1);

  CvMat* training_classifications = cvCreateMat(number_of_training_samples, number_of_classes, CV_32FC1);

  cvZero(training_classifications);

  // define testing data storage matrices
  CvMat* testing_data = cvCreateMat(number_of_testing_samples, attributes_per_sample, CV_32FC1);

  CvMat* testing_classifications = cvCreateMat(number_of_testing_samples, number_of_classes, CV_32FC1);

  cvZero(testing_classifications);

  // define classification output vector

  CvMat* classificationResult = cvCreateMat(1, number_of_classes, CV_32FC1);
  CvPoint max_loc = {0,0};

  // load training and testing data sets

  if (  read_data_from_csv(argv[1], training_data, training_classifications, number_of_training_samples) &&
        read_data_from_csv(argv[2], testing_data, testing_classifications, number_of_testing_samples))
  {
    // define the parameters for the neural network (MLP)

    // set the network to be 3 layer 256->10->10
    // - one input node per attribute in a sample
    // - 10 hidden nodes
    // - one output node per class

    // note that the OpenCV neural network (MLP) implementation does not
    // support categorical variables explicitly.
        // So, instead of the output class label, we will use
        // a binary vector of {0,0 ... 1,0,0} components (one element by class)
    // for training and therefore, MLP will give us a vector of "probabilities"
    // at the prediction stage - the highest probability can be accepted
    // as the "winning" class label output by the network

    int layers_d[] = { attributes_per_sample, 10,  number_of_classes};
    CvMat* layers = cvCreateMatHeader(1,3,CV_32SC1);
    cvInitMatHeader(layers, 1,3,CV_32SC1, layers_d);

    // create the network using a sigmoid function with alpha and beta
    // parameters 0.6 and 1 specified respectively (refer to manual)

    CvANN_MLP* nnetwork = new CvANN_MLP;
    nnetwork->create(layers, CvANN_MLP::SIGMOID_SYM, 0.6, 1);

    // set the training parameters

    CvANN_MLP_TrainParams params = CvANN_MLP_TrainParams(
          // terminate the training after either 1000
          // iterations or a very small change in the
          // network wieghts below the specified value
          cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 1000, 0.000001),

          // use backpropogation for training
          CvANN_MLP_TrainParams::BACKPROP,

          // co-efficents for backpropogation training
          // (refer to manual)
          0.1,
          0.1);

    // train the neural network (using training data)

    printf( "\nUsing training database: %s\n", argv[1]);

    int iterations = nnetwork->train(training_data, training_classifications, NULL, NULL, params);

    printf( "Training iterations: %i\n\n", iterations);

    // perform classifier testing and report results

    CvMat test_sample;
    int correct_class = 0;
    int wrong_class = 0;
    int false_positives [number_of_classes] = {0,0,0,0,0,0,0,0,0,0};

    printf( "\nUsing testing database: %s\n\n", argv[2]);

    for (int tsample = 0; tsample < number_of_testing_samples; tsample++)
    {
      // extract a row from the testing matrix

      cvGetRow(testing_data, &test_sample, tsample );

      // run neural network prediction

      nnetwork->predict(&test_sample, classificationResult);

        // The NN gives out a vector of probabilities for each class
        // We take the class with the highest "probability"
        // for simplicity (but we really should also check separation
        // of the different "probabilities" in this vector - what if
        // two classes have very similar values ?)

        cvMinMaxLoc(classificationResult, 0, 0, 0, &max_loc, 0 );

      printf("Testing Sample %i -> class result (digit %d)\n", tsample, max_loc.x);

      // if the corresponding location in the testing classifications
      // is not "1" (i.e. this is the correct class) then record this

      if (!(CV_MAT_ELEM(*testing_classifications, float, tsample, max_loc.x)))
      {
        // if they differ more than floating point error => wrong class
        wrong_class++;

        false_positives[(int) max_loc.x]++;
      }
      else
      {
        // otherwise correct

        correct_class++;
        }
    }

    printf( "\nResults on the testing database: %s\n"
        "\tCorrect classification: %d (%g%%)\n"
        "\tWrong classifications: %d (%g%%)\n",
    argv[2],
    correct_class, (double) correct_class*100/number_of_testing_samples,
        wrong_class, (double) wrong_class*100/number_of_testing_samples);

    for (int i = 0; i < number_of_classes; i++)
    {
      printf( "\tClass (digit %d) false postives  %d (%g%%)\n", i,
           false_positives[i],
           (double) false_positives[i]*100/number_of_testing_samples);
    }


    // free all memory

    cvReleaseMat( &training_data );
    cvReleaseMat( &training_classifications );
    cvReleaseMat( &testing_data );
    cvReleaseMat( &testing_classifications );
    cvReleaseMat( &classificationResult);

     // all OK : main returns 0

       return 0;
    }

    // not OK : main returns -1

    return -1;
}
/******************************************************************************/

