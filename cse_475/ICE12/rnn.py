"""
Tyler Fichiera - Module 11 In-class Exercise
CSE 475 - Fall '23
"""

'''
In this ICE, we will write a RNN model.  
Name this file rnn.py.
'''

import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F


torch.manual_seed(42)


# Suppose our model takes in input with shape (batch_size, sequence_length, input_feature_size), we need to classify each sequence into 3 classes
# we want our architecture to be:
# x -> RNN -> Linear
# For RNN, we use hidden size of 1024 and 2 layers 
# nn.RNN: https://pytorch.org/docs/stable/generated/torch.nn.RNN.html
class RNN(nn.Module):
    def __init__(self, input_feature_size, hidden_size, num_layers, num_classes, sequence_length):
        super(RNN, self).__init__()

        self.hidden_size = hidden_size
        self.num_layers = num_layers

        # Define RNN with hidden size, input feature size, and number of layers. 
        # Pay attention to the batch_first=True arguement here and understand what it means.
        self.rnn = nn.RNN(input_size=input_feature_size, hidden_size=hidden_size, num_layers=num_layers, batch_first=True)

        # Recall that each time step output a hidden state, we will concatenate all those vectoes as input to a linear layer. 
        # The output of the linear layer is the number of classes
        self.fc = nn.Linear(hidden_size * sequence_length, num_classes)
    
    def forward(self, x): # x: (batch_size, sequence_length, input_feature_size)
        # we need to initialize the initial hidden state, h0 
        # h0: (num_layers, batch_size, hidden_size)
        h0 = torch.zeros(self.num_layers, x.size(0), self.hidden_size)

        # RNN output two things, see RNN documentation for more illustration on shape of the output. We will only use the first output.
        # out: hidden states of all time steps
        # h_last: hidden states of last time step only
        out, h_last = self.rnn(x, h0)

        # As illustrated in __init__, we need to flatten hidden states of all time steps and feed it into a linear layer.
        # We want to flatten into size of (batch_size, ...)
        out = out.reshape(x.size(0), -1)
        out = self.fc(out)

        return out # (batch_size, num_classes)


# let's test this rnn, and suppose x is the input to this RNN
x = torch.randn(10, 5, 512) # 10 sequences (batch_size), 5 time steps for each sequence (sequence length), each time step has 512 features

sequence_length = x.size(1)
input_feature_size = x.size(2)
hidden_size = 1024
num_layers = 2
num_classes = 3

# we will check the shape of the output vector 
model = RNN(input_feature_size, hidden_size, num_layers, num_classes, sequence_length) 
out_shape = list(model(x).shape)
print(out_shape)

# we are also checking the shape of the feed forward layer (self.fc) in the network 
for name, param in model.named_parameters():
    if name == "fc.weight":
        fc_shape = list(param.shape)
print(fc_shape)
