# Homework_1
# 2023年3月24日15:26:06

# import bitcoin
from bitcoin import *

my_private_key = random_key()
print("Private Key: %s\n" % my_private_key)

#Generate Public Key
my_public_key = privtopub(my_private_key)
print("Public Key: %s\n" % my_public_key)

#Create a bitcoin address
my_bitcoin_address = pubtoaddr(my_public_key)
print("Bitcoin Address: %s\n" % my_bitcoin_address)

#Create a multi-signature bitcoin address
my_private_key1 = random_key()
my_private_key2 = random_key()
my_private_key3 = random_key()

print("Private Key1: %s\n" % my_private_key1)
print("Private Key2: %s\n" % my_private_key2)
print("Private Key3: %s\n" % my_private_key3)

#Generate three public key
my_public_key1 = privtopub(my_private_key1)
my_public_key2 = privtopub(my_private_key2)
my_public_key3 = privtopub(my_private_key3)

print("Public Key1: %s\n" % my_public_key1)
print("Public Key2: %s\n" % my_public_key2)
print("Public Key3: %s\n" % my_public_key3)

#Create multi-signature address
my_multi_sig = mk_multisig_script(my_private_key1, my_private_key2, my_private_key3, 2, 3)
my_multi_address = scriptaddr(my_multi_sig)
print("Multi signature address: %s" % my_multi_address)

a_valid_bitcoin_address = 'bc1qfn3xcsjzzjjg77jw8v06v22qls8wmvex45plfl'
# print(history(a_valid_bitcoin_address))
for element in history(a_valid_bitcoin_address):
    print(element)




