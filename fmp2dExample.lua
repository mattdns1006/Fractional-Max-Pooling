require "nn"

x = torch.range(1,100):resize(1,10,10)
fmp = nn.SpatialFractionalMaxPooling(2,2,0.7,0.7)
y=  fmp:forward(x)
