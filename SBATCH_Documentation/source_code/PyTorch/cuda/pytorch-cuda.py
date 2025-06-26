import torch
import torch.nn as nn

model = nn.Linear(10, 1)
input_data = torch.rand(100, 10)

device = torch.device(torch.accelerator.current_accelerator())
model.to(device)
input_data = input_data.to(device)

output = model(input_data)
print(f"Output tensor device: {output.device}")
