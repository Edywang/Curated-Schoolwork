from tensorflow.keras import layers, models, optimizers
from feature_extraction import conv_base

# Define a sequential model here
model = models.Sequential([
    conv_base,
    layers.Conv2D(32, 5, activation='relu'),
    layers.MaxPool2D(pool_size=(2,2)),
    layers.Conv2D(32, 3, activation='relu'),
    layers.Conv2D(32, 5, activation='relu'),
    layers.Conv2D(32, 7, activation='relu'),
    layers.MaxPool2D(pool_size=(2,2)),
    layers.Flatten(),
    layers.Dense(32, activation='relu'),
    layers.Dense(1, activation='sigmoid')
])

# Then, call model.compile()
model.compile(
    loss='binary_crossentropy',
    optimizer=optimizers.RMSprop(lr=1e-4),
    metrics=['acc']
)

# Finally, train this compiled model by running:
# python train_dropout.py