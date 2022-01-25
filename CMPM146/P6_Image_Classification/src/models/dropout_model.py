from tensorflow.keras import layers
from tensorflow.keras import models
from tensorflow.keras import optimizers

# Define your dropout model here

model = models.Sequential([
    layers.Conv2D(64, 3, input_shape=(150,150,3)),
    layers.Activation('relu'),
    layers.MaxPool2D(pool_size=2),
    layers.Conv2D(128, 3),
    layers.Activation('relu'),
    layers.MaxPool2D(pool_size=2),
    layers.Conv2D(256, 3),
    layers.Activation('relu'),
    layers.MaxPool2D(pool_size=2),
    layers.Conv2D(256, 3),
    layers.Activation('relu'),
    layers.MaxPool2D(pool_size=2),
    
    layers.Flatten(),
    layers.Dropout(.75),
    layers.Dense(512, activation='relu'),
    layers.Dropout(.35),
    layers.Dense(512, activation='relu'),
    layers.Dense(1, activation='sigmoid'),
    ])

# Then, call model.compile()
model.compile(
    loss='binary_crossentropy',
    optimizer=optimizers.RMSprop(learning_rate=1e-4),
    metrics=['acc']
)

# Train this compiled model by modifying basic_train 
# to import this model, then run:
#   python train.py
