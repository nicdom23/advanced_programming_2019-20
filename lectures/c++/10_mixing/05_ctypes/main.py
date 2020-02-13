#/usr/bin/env python3

from ctypes import *
dso = CDLL("./libhello.so") # import shared object on POSIX compatible OS
#open the shared library
## functions w/o args
dso.hello()#functions are memebers of this object


## strings
dso.repeat.argtypes = [c_char_p]#invoke the name of the funcitons and defines a list of the argument i need to give
dso.repeat.restype = c_int#defines the return type, always a return value
res = dso.repeat(b"ctypes are great") # use b to pass read-only variable(transform strings into bytecode, strings are passed from python to c using b in front

# use create_string_buffer for a "mutable string"// buf can be modified
buf = create_string_buffer(b"this could be modified")#this returns a char pointer that can be passed to repeat
dso.repeat(buf)


## arrays
size = 10  #int is a class that has members, c_types provides a way to pass from python objects to c objects
d_array = (c_double*size)()  # better do the allocation on the python side (python has a garbage collector, no memory leaks  //returns a pointer to an array of doubles

for i in range(size):#simply initialize
    d_array[i] = i

array_sum = dso.array_sum  #use sticky note on the same object

array_sum.argtypes = [POINTER(c_double), c_size_t] # note the use of POINTER//needs to be used instead of _p
array_sum.restype = c_double

print("the sum of d_array is", array_sum(d_array,size))#now i can call the funciton as a normal python function


## structs    HOW TO DEAL WITH STRUCTS(THEY CAN ONLY HAVE VARIABLES NOT FUNCTIONS)
class data(Structure):
    _fields_ = [("i",c_int),#a list of ordered tuples
                ("name",c_char_p),
                ("energy",c_double)] # order is crucial otherwise seg-fault
#now this is a regular python class
param = data(name=b"Alberto", energy=99.9, i=42)

#dso.use_by_value.argtypes = [data]   #uncomment if you want to be pedantic
dso.use_by_value(param) # default is by value

param.i=77
param.name=b"ciao ciao"

# dso.use_by_reference.argtypes = [POINTER(data)]  #this is another
# dso.use_by_reference(param)                      #way to do the below line
dso.use_by_reference(byref(param))

dso.set_energy.argtypes = [POINTER(data), c_double]

dso.set_energy(param, 32.45)

dso.use_by_value(param)

#to call c++ we need to write a C interface
