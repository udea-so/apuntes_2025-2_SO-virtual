from time import sleep

padding = 15
process_a = [('Process A', 5), ('Process A', 4), ('Process A', 3), ('Process A', 2), ('Process A', 1), ('SWITCH!', 0)]
process_b = [('Process B', 5), ('Process B', 4), ('Process B', 3), ('Process B', 2), ('Process B', 1), ('SWITCH!', 0)]

print()
print('Process'.ljust(padding), end='')
print('Time')

print((len('Time') + padding) * '-')

for t in process_a:
  print(t[0].ljust(padding), end=' ')
  print(t[1])
  sleep(0.5)
  
print()

for t in process_b:
  print(t[0].ljust(padding), end=' ')
  print(t[1])
  sleep(0.5)

print()