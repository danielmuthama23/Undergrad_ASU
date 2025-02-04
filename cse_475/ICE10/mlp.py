"""
Tyler Fichiera - Module 10 In-class Exercise
CSE 475 - Fall '23
"""

'''
We will use a sinple multi-layer perceptron network in this lab to learn a quadratic function X^2 = Y` where `x` is a single dimension input variable and Y is a single dimension target variable.  
Name this file mlp.py.

We will use pytorch in this in class activity, you can use command 'pip install torch' to install torch on your local machine to develop your code or you can just use colab where torch is pre-installed.

The code needs you to implement is labeled by TO DO !!!!!, there is not much for you to implement but do learn about the entire workflow.

Name your file mlp.py when submitting to GradeScope.
'''

import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F


torch.manual_seed(42)


class Net(nn.Module):

    def __init__(self):
        super(Net, self).__init__()

        # Here you will need to define two single-layer perceptron (with non-linearality) to form a two-layer perceptron network.
        # Input is 1 dimension, we will make intermediate dimension to be 10, final output dimension is also 1. Below is the network:
        # X (1 dimension) -> 10 dimensional internal layer -> Relu -> Y (1 dimension)
        # We use nn.Linear for a single-layer perceptron as in previous ICE.
        # For ReLU implementation, we will use F.relu (https://pytorch.org/docs/stable/generated/torch.nn.functional.relu.html)
        self.fc1 = nn.Linear(1, 10)  # TO DO !!!!!
        self.fc2 = nn.Linear(10, 1)  # TO DO !!!!!

    def forward(self, x):
        out = self.fc1(x)  # TO DO !!!!! pass through self.fc1
        out = F.relu(out)   # TO DO !!!!! pass through F.relu
        out = self.fc2(out)  # TO DO !!!!! pass through self.fc2
        return out


net = Net()

# we use SGD optimizer with a learning rate of 0.05
optimizer = optim.SGD(net.parameters(), lr=0.05) # TO DO !!!!!

# creating the data: we created 1000 points for quadratic function learning
X = 2 * torch.rand(1000) - 1 # X range is [-1, 1]
Y = X ** 2

# train 10 epochs
for epoch in range(10): # TO DO !!!!!
    epoch_loss = 0 
    for i, (x, y) in enumerate(zip(X, Y)):
        x = torch.unsqueeze(x, 0)  # TO DO !!!!!
        y = torch.unsqueeze(y, 0)  # TO DO !!!!!

        optimizer.zero_grad()

        output = net(x) # TO DO !!!!!

        loss = nn.MSELoss()(output, y) # TO DO !!!!!

        loss.backward()

        optimizer.step()

        epoch_loss += loss.item()

    print("Epoch {} - loss: {}".format(epoch + 1, epoch_loss))


# let's test our model
# let's see if we can predict 0.5 * 0.5 = 0.25, 0.3 * 0.3 = 0.09, 0.2 * 0.2 = 0.04
X_test = torch.tensor([0.5, 0.3, 0.2])
Y_test = net(X_test.unsqueeze(1))
Y_test = Y_test.flatten().tolist()
Y_test = [round(y, 2) for y in Y_test]
