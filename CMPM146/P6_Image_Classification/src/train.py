import matplotlib.pyplot as plt
# from models.basic_model import model
from models.dropout_model import model
from preprocess import train_generator, validation_generator

print(model.summary())
# Train the model defined in basic_model.py
history = model.fit(train_generator, steps_per_epoch=100, epochs=100, validation_data=validation_generator, validation_steps=50)

# Save the model weights
# Change the name of this file to avoid overwriting previously trained models
model.save('cats_and_dogs_small_1.h5')

# Plot the  loss and accuracy over the training run
def plot(history):
    acc = history.history['acc']
    val_acc = history.history['val_acc']
    loss = history.history['loss']
    val_loss = history.history['val_loss']
    
    epochs = range(1, len(acc) + 1)
    plt.plot(epochs, acc, 'bo', label='Training acc')
    plt.plot(epochs, val_acc, 'b', label='Validation acc')
    plt.title('Training and validation accuracy')
    plt.legend()
    plt.figure()
    plt.plot(epochs, loss, 'bo', label='Training loss')
    plt.plot(epochs, val_loss, 'b', label='Validation loss')
    plt.title('Training and validation loss')
    plt.legend()
    plt.show()

plot(history) if input('Show plots? [y/N]').lower() == 'y' else print()
