# Importing Keras libraries
from keras.applications.resnet50 import ResNet50, preprocess_input
from keras.layers import Dense, MaxPooling2D, Flatten, Conv2D, Dropout
from keras.models import Model
from keras.optimizers import SGD
from keras.preprocessing.image import ImageDataGenerator

from IPython import get_ipython
ipy = get_ipython()
if ipy is not None:
    ipy.run_line_magic('matplotlib', 'inline')
from keras import backend as K

# we need to get gather more data

# this is where your training and testing data (images) need to be relative to
# where your script (altimeter_nn.py) is
train_data_dir = '../images/train'
validation_data_dir = '../images/validation'

# dimensions of images
IMG_WIDTH, IMG_HEIGHT = 256, 256

if K.image_data_format() == 'channels_first':
    input_shape = (3, IMG_WIDTH, IMG_HEIGHT)
else:
    input_shape = (IMG_WIDTH, IMG_HEIGHT, 3)


# Set up resnet layers
res_model = ResNet50(include_top = False, pooling = 'avg', input_shape=(IMG_WIDTH, IMG_HEIGHT,3), weights = 'imagenet')

# Taking the output of the last convolution block in ResNet50
x = res_model.output

# Set up output layer
predictions = Dense(3, activation='softmax')(x) # add layers and play with training up a model before attaching it to resnet

# Model to be trained
model = Model(input=res_model.input, outputs=predictions)

# # Training only top layers i.e. the layers which we have added in the end
# for layer in res_model.layers:
#     layer.trainable = False

# We will try to train the last stage of ResNet50
for layer in res_model.layers[0:140]:
  layer.trainable = False
 
for layer in res_model.layers[140:]:
  layer.trainable = True


model.summary()

# Compiling the CNN
model.compile(optimizer = SGD(lr = 0.01, decay = 1e-6, momentum = 0.9, nesterov = True), loss = 'categorical_crossentropy', metrics = ['accuracy']) # try different loss functions and optimizers

data_generator = ImageDataGenerator(preprocessing_function=preprocess_input) # Play with more skewing, scaling, etc.

# Proving the path of training and test dataset
# Setting the image input size as (224, 224)
# We are using class mode as binary because there are only two classes in our data
training_set = data_generator.flow_from_directory(train_data_dir,
                                                 target_size = (IMG_WIDTH, IMG_HEIGHT),
                                                 batch_size = 32,
                                                 class_mode = 'categorical')
 
test_set = data_generator.flow_from_directory(validation_data_dir,
                                            target_size = (IMG_WIDTH, IMG_HEIGHT),
                                            batch_size = 32,
                                            class_mode = 'categorical')
 
# Training the model for 10 epochs
history=model.fit_generator(training_set,
                         steps_per_epoch = 500,
                         epochs = 10,
                         validation_data = test_set,
                         validation_steps = 100,
                         verbose=1)


from keras.utils import plot_model
plot_model(model, to_file='model.png')

import matplotlib.pyplot as plt


# Plot training & validation accuracy values
plt.plot(history.history['acc'])
plt.plot(history.history['val_acc'])
plt.title('Model accuracy')
plt.ylabel('Accuracy')
plt.xlabel('Epoch')
plt.legend(['Train', 'Test'], loc='upper left')
plt.show(block=False)

# create a new, numbered file for the results chart and save it in the catdog file
import os

i = 0
while os.path.exists("C:/Users/Alec Otterson/OneDrive - BYU-Idaho/AlecDocs/AI/DroneAlt/CNN/alt1Charts/acc%s.png" % i):
    i += 1

plt.savefig("C:/Users/Alec Otterson/OneDrive - BYU-Idaho/AlecDocs/AI/DroneAlt/CNN/alt1Charts/acc%s.png" % i)

model.save_weights("C:/Users/Alec Otterson/OneDrive - BYU-Idaho/AlecDocs/AI/DroneAlt/CNN/alt1Weights/weight%s.h5" % i)

# add loss chart