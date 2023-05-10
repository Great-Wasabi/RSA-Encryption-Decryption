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

def generate_p_q_primes(min, max):
    p, q = generatePrime(min, max), generatePrime(min, max)
    while p == q:
        q = generatePrime(min, max)
    return p, q

def generate_n(p, q):
    return p * q

def generate_phi_n(p, q):
    return (p-1) * (q-1)

def generatePublicKey(phi_n):
    e = random.randint(3, phi_n-1)
    while math.gcd(e, phi_n) != 1:
        e = random.randint(3, phi_n-1)
    return e    

def generatePrivateKey(e, phi):
    for d in range(3, phi):
        if (d * e) % phi == 1:
            return d
    raise ValueError("modular inverse does not exist")

def encrypt(message, e, n):
    return [pow(ord(char), e, n) for char in message]

def decrypt(cipher, d, n):
    return "".join([chr(pow(char, d, n)) for char in cipherText])

if __name__ == '__main__':
    p, q = generate_p_q_primes(10000, 100000)
    n = generate_n(p, q)
    phi_n = generate_phi_n(p, q)
    e = generatePublicKey(phi_n)
    d = generatePrivateKey(e, phi_n)

#    print("p (Generated Number between 10000 and 100000): ", p)
#    print("q (Generated Number between 10000 and 100000): ", q)
#    print("n (p * q): ", n)
#    print("phi_n (p-1 * q-1): ", phi_n)
#    print("Public Key (e) (e is a number between 3 and phi_n-1 that is not coprime to phi_n): ", e)
#    print("Private Key (d) (d is a number such that (e*d)%phi_n = 1): ", d)
#    print("Check : ", e*d%phi_n)
    

    message = "Hello World"
    print("Initial Message: ",message)
    cipherText =  encrypt(message, e, n)
    print("Cipher Text: ", cipherText)
    message_final = decrypt(cipherText, d, n)
    print(message_final)







