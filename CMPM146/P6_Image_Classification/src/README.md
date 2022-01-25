## Setup

First, install the requirements. If you get an error, try replacing `pip` with `pip3`.

    pip install -r requirements.txt

## Get the data
You need to download the data from [kaggle](www.kaggle.com/c/dogs-vs-cats/data).

Unzip it to a new directory, `./kaggle`.

# Preprocess

Split the dataset into 1000 training images, 500 test images, and 500 validation images for each dog / cat label.

    python train_test_split.py

Now examine and run `preprocess.py`.
This defines a generator function that will provide each image with pixel values rescaled to [0...1].

    python preprocess.py

# Train the basic model

Train a convolutional network to predict if an image is a dog or a cat.

    python train.py

This will call the model that you define in `basic_model.py`.


See the writeup for further instructions.