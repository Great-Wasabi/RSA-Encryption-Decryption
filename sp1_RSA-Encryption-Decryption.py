import math
import random
import time

def isPrime(number):
    if number <= 1:
        return False
    for i in range(2, int(math.sqrt(number))+1):
        if number%i == 0:
            return False
    return True

def generatePrime(min, max):
    prime = random.randint(min, max)
    while not isPrime(prime):
        prime = random.randint(min, max)
    return prime

def mod_inverse(e, phi):
    for d in range(3, phi):
        if (d * e) % phi == 1:
            return d
    raise ValueError("modular inverse does not exist")

p, q = generatePrime(1000, 10000), generatePrime(1000, 10000)
while p == q:
    q = generatePrime(1000, 10000)

n = p * q 
phi_n = (p-1) * (q-1)

e = random.randint(3, phi_n-1)
while math.gcd(e, phi_n) != 1:
    e = random.randint(3, phi_n-1)

d = mod_inverse(e, phi_n)

print("Public Key (e) : ", e)
print("Private Key (d) : ", d)
print("n : ", n)
print("phi_n : ", phi_n)
print("p : ", p)
print("q : ", q)

message = "Hello World"
messageEncoded = [ord(char) for char in message]
cipherText = [pow(char, e, n) for char in messageEncoded]
print(cipherText)