from tensorflow.keras.preprocessing.image import ImageDataGenerator
from keras.preprocessing import image
from tensorflow.keras import layers
import matplotlib.pyplot as plt
import random

train_dir = 'cats_and_dogs_small/train/'
validation_dir = 'cats_and_dogs_small/validation/'

# Create the data generators (each should be an instance of ImageDataGenerator)
# Rescale all images from the [0...255] range to the [0...1] range
# train_datagen = ImageDataGenerator(preprocessing_function=train_preprocess)
train_datagen = ImageDataGenerator(rescale=1./255, horizontal_flip=True, vertical_flip=True)
# train_datagen = ImageDataGenerator(preprocessing_function=test_preprocess)
test_datagen = ImageDataGenerator(rescale=1./255)


# Call flow_from_directory on each of your datagen objects
# train_generator = train_datagen.flow_from_directory(directory=train_dir, target_size=(150,150), batch_size=20, class_mode='binary')
train_generator = train_datagen.flow_from_directory(directory=train_dir,
                                                    target_size=(150,150), 
                                                    batch_size=20, 
                                                    class_mode='binary', 
                                                    shuffle=True)
# print(type(train_generator))
validation_generator = test_datagen.flow_from_directory(directory=validation_dir, 
                                                        target_size=(150,150), 
                                                        batch_size=20, 
                                                        class_mode='binary')

# Usage Example:
for data_batch, labels_batch in train_generator:
    print('data batch shape:', data_batch.shape)
    print('labels batch shape:', labels_batch.shape)
    break


def show_example_images(datagen):
    """
    Use this function to show some example images from the data generator.

    :param datagen: The data generator.
    """
    fnames = [os.path.join(train_cats_dir, fname) for
        fname in os.listdir(train_cats_dir)]
    print(len(fnames))
    img_path = fnames[3]            # Chooses one image to augment
    img = image.load_img(img_path, target_size=(150, 150))
    x = image.img_to_array(img)     # Converts it to a Numpy array with shape (150, 150, 3) 
    x = x.reshape((1,) + x.shape)   # Reshapes it to (1, 150, 150, 3)
    i = 0
    for batch in datagen.flow(x, batch_size=1):
        plt.figure(i)
        imgplot = plt.imshow(image.array_to_img(batch[0]))
        i += 1
        if i % 4 == 0:
            break
    plt.show()
