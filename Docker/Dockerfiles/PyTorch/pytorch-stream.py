import torch
import time
device = torch.device(torch.accelerator.current_accelerator())
def heavy_computation(tensor):
	return tensor**2 + (tensor**3) * (tensor.sin() * tensor.cos()) + tensor.tan()
size = 10**9
data = torch.randn(size, device=device, dtype=torch.float16)
stream1 = torch.cuda.Stream(device=device)
stream2 = torch.cuda.Stream(device=device)
torch.cuda.synchronize()
start_time = time.time()
with torch.cuda.stream(stream1):
	result1 = heavy_computation(data[:size // 2])
with torch.cuda.stream(stream2):
	result2 = heavy_computation(data[size // 2:])
torch.cuda.synchronize()
print(f"Time taken with streams: {time.time() - start_time:.3f} seconds.")
torch.cuda.synchronize()
start_time = time.time()
result1_seq = heavy_computation(data[:size // 2])
result2_seq = heavy_computation(data[size // 2:])
torch.cuda.synchronize()
print(f"Time taken without streams: {time.time() - start_time:.3f} seconds.")
