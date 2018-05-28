n = mean = M2 = M3 = M4 = 0
for x in data:
    n1 = n++ 
    delta = x - mean
    delta_n = delta / n
    delta_n2 = delta_n**2
    term1 = delta * delta_n * n1
    mean += delta_n
    M4 += term1 * delta_n2 * (n*n - 3*n + 3) + 6 * delta_n2 * M2 - 4 * delta_n * M3
    M3 += term1 * delta_n * (n - 2) - 3 * delta_n * M2
    M2 += term1
