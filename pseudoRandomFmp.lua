require "nn"

nIn = 20 
fmp = 0.7
poolSize = 2
nOut = math.floor(nIn*fmp)
print(string.format("INPUT SIZE = %d, FMP ratio = %f, OUTPUT SIZE = %d",nIn,fmp,nOut))

x = torch.range(1,nIn*nIn):resize(1,nIn,nIn)
fmp = nn.SpatialFractionalMaxPooling(2,2,0.7,0.7)
y =  fmp:forward(x)

print("Input and output shapes ==>")
print(x:size())
print(y:size())

a = {}
for i=1,nOut do 
	alpha = (nIn - poolSize)/(nOut - 1)
	--u = fmp.randomSamples[1][1][1]
	u = 0.4
	a_ = alpha*(i+u)
	a[i] = math.ceil(a_)
	if i > 1 then
		print(string.format("i = %d, u = %f, alpha = %f, a (before ceil) %f, a_i = %d, di = %d ",i,u,alpha,a_,a[i],a[i]-a[i-1]))
	else
		print(string.format("i = %d, u = %f, alpha = %f, a (before ceil) %f, a_i = %d",i,u,alpha,a_,a[i]))
	end
end



