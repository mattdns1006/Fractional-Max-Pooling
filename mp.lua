require "nn"

x = torch.rand(1,1,4,4,4)
mp2 = nn.VolumetricMaxPooling(2,2,2)

o = mp2:forward(x)
o:fill(1) -- say gradient is one 

print(x)
print(o)
print(mp2:backward(x,o))
