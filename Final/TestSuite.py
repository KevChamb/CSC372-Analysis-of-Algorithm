from MainStarter import *
import time

def test1():
    print("-----Test 1--------------------")
    print("Output from function:")
    #Test output for wrong amount of Transmitters
    Reciever = [(1, 4), (2, 4), (7, 4)]
    Transmitter = [(4, 4), (6, 2)]
    Obstruction = [(1, 2), (1, 5), (8, 5), (8, 3), (11, 3), (11, 1), (5, 1), (5, 3), (4, 3), (4, 1), (1, 1), (1, 2)]
    test = isPaired(Reciever, Transmitter)
    result1 = False
    if(test == result1):
        print("PASS")
    else:
        print("FAIL")


def test2():
    print("-----Test 2--------------------")
    see = 0
    obstruct = 0
    Obstruction = [(1, 2), (1, 5), (8, 5), (8, 3), (11, 3), (11, 1), (5, 1), (5, 3), (4, 3), (4, 1), (1, 1), (1, 2)]
    Reciever = [(2, 4), (2, 2), (5, 4)]
    Transmitter = [(6, 2), (7, 4), (6, 3)]
    for i, antena in enumerate(Reciever):
        for j, transmit in enumerate(Transmitter):
            if not lineOfSight(antena, transmit, Obstruction):
                see += 1
            else:
                obstruct += 1

    if see == 4 and obstruct == 5:
        print("PASS")
    else:
        print("FAIL")
        print("Expected: 4 seen, 5 obstructed")
        print("Recieved: " + str(see) + " seen, " + str(obstruct) +" obstructed")


def test3():
    #Testing a set of 3 recievers and transmitters
    Obstruction = [(1, 2), (1, 5), (8, 5), (8, 3), (11, 3), (11, 1), (5, 1), (5, 3), (4, 3), (4, 1), (1, 1), (1, 2)]
    Reciever = [(2,4),(2,2),(5,4)]
    Transmitter = [(4,4),(6,3),(6,2)]
    print("-----Test 3--------------------")
    print("Output from function:")
    expected = "All troops are communicating."
    recieved = runSystem(Reciever, Transmitter, Obstruction)
    if recieved == expected:
        print("PASS")
    else:
        print('FAIL')
        print("Expected output: " + str(expected))
        print("Recieved output: " + str(recieved))

def test4():
    Obstruction = [(1, 2), (1, 5), (8, 5), (8, 3), (11, 3), (11, 1), (5, 1), (5, 3), (4, 3), (4, 1), (1, 1), (1, 2)]
    Reciever = [(2, 4), (2, 2), (5, 4)]
    Transmitter = [(6, 2), (7, 4), (6, 3)]
    print("-----Test 4--------------------")
    print("Output from function:")
    expected = "Your troops can't communicate!"
    recieved = runSystem(Reciever, Transmitter, Obstruction)
    if recieved == expected:
        print("PASS")
    else:
        print('FAIL')
        print("Expected output: " + str(expected))
        print("Recieved output: " + str(recieved))


def test5(): #n=6
    Obstruction = [(1, 2), (1, 6), (8, 6), (8, 4), (11, 4), (11, 0), (5, 0), (5, 4), (4, 4), (4, 0), (1, 0), (1, 2)]
    Reciever = [(2,2),(3,3),(6,5),(7,1),(10,3),(8,3)]
    Transmitter = [(2,5),(4,5),(5,5),(9,2),(8,1),(7,4)]
    print("-----Test 5--------------------")
    print("Output from function:")
    expected = "All troops are communicating."
    recieved = runSystem(Reciever, Transmitter, Obstruction)
    if recieved == expected:
        print("PASS")
    else:
        print('FAIL')
        print("Expected output: " + str(expected))
        print("Recieved output: " + str(recieved))

def test6(): #n=9
    Obstruction = [(1, 2), (1, 5), (8, 5), (8, 3), (11, 3), (11, 1), (5, 1), (5, 3), (4, 3), (4, 1), (1, 1), (1, 2)]
    Reciever = [(2,2),(3,3),(6,5),(7,1),(10,3),(8,3),(3,2),(6,1),(7,5)]
    Transmitter = [(2,5),(4,5),(5,5),(9,2),(8,1),(7,4),(3,4),(9,1),(3,1)]
    print("-----Test 6--------------------")
    print("Output from function:")
    expected = "All troops are communicating."
    recieved = runSystem(Reciever, Transmitter, Obstruction)
    if recieved == expected:
        print("PASS")
    else:
        print('FAIL')
        print("Expected output: " + str(expected))
        print("Recieved output: " + str(recieved))

def test7(): #n=12
    Obstruction = [(1, 2), (1, 5), (8, 5), (8, 3), (11, 3), (11, 1), (5, 1), (5, 3), (4, 3), (4, 1), (1, 1), (1, 2)]
    Reciever = [(2,2),(3,3),(6,5),(7,1),(10,3),(8,3),(3,2),(6,1),(7,5),(2,1),(6,2),(7,2)]
    Transmitter = [(2,5),(4,5),(5,5),(9,2),(8,1),(7,4),(3,4),(9,1),(3,1),(10,1),(8,2),(2,3)]
    print("-----Test 7--------------------")
    print("Output from function:")
    expected = "All troops are communicating."
    recieved = runSystem(Reciever, Transmitter, Obstruction)
    if recieved == expected:
        print("PASS")
    else:
        print('FAIL')
        print("Expected output: " + str(expected))
        print("Recieved output: " + str(recieved))


def test8(): #n=12
    Obstruction = [(1, 2), (1, 5), (8, 5), (8, 3), (11, 3), (11, 1), (5, 1), (5, 3), (4, 3), (4, 1), (1, 1), (1, 2)]
    Reciever = [(2,2),(3,3),(6,5),(7,1),(10,3),(8,3),(3,2),(6,1),(7,5),(2,1),(6,2),(7,2)]
    Transmitter = [(12, 2), (7, 4), (6, 3),(9,2),(8,1),(7,4),(3,4),(9,1),(3,1),(10,1),(8,2),(2,3)]
    print("-----Test 8--------------------")
    print("Output from function:")
    expected = "Your troops can't communicate!"
    recieved = runSystem(Reciever, Transmitter, Obstruction)
    if recieved == expected:
        print("PASS")
    else:
        print('FAIL')
        print("Expected output: " + str(expected))
        print("Recieved output: " + str(recieved))


def test9(): #n=15
    Obstruction = [(1, 2), (1, 5), (8, 5), (8, 3), (11, 3), (11, 1), (5, 1), (5, 3), (4, 3), (4, 1), (1, 1), (1, 2)]
    Reciever = [(2,2),(3,3),(6,5),(7,1),(10,3),(8,3),(3,2),(6,1),(7,5),(2,1),(6,2),(7,2),(6,3),(9,3),(2,4)]
    Transmitter = [(2,5),(4,5),(5,5),(9,2),(8,1),(7,4),(3,4),(9,1),(3,1),(10,1),(8,2),(2,3),(7,3),(3,5),(10,2)]
    print("-----Test 9--------------------")
    print("Output from function:")
    expected = "All troops are communicating."
    recieved = runSystem(Reciever, Transmitter, Obstruction)
    if recieved == expected:
        print("PASS")
    else:
        print('FAIL')
        print("Expected output: " + str(expected))
        print("Recieved output: " + str(recieved))


def test10(): #n=15
    Obstruction = [(1, 2), (1, 5), (8, 5), (8, 3), (11, 3), (11, 1), (5, 1), (5, 3), (4, 3), (4, 1), (1, 1), (1, 2)]
    Reciever = [(2,2),(3,3),(6,5),(7,1),(10,3),(8,3),(3,2),(6,1),(7,5),(2,1),(6,2),(7,2),(6,3),(9,3),(2,4)]
    Transmitter = [(2,5),(4,5),(5,5),(9,2),(8,1),(7,4),(3,4),(9,1),(12,1),(10,1),(8,2),(2,3),(7,3),(3,5),(10,2)]
    print("-----Test 10--------------------")
    print("Output from function:")
    expected = "Your troops can't communicate!"
    recieved = runSystem(Reciever, Transmitter, Obstruction)
    if recieved == expected:
        print("PASS")
    else:
        print('FAIL')
        print("Expected output: " + str(expected))
        print("Recieved output: " + str(recieved))


def timeTest():
    Obstruction = [(1, 2), (1, 5), (8, 5), (8, 3), (11, 3), (11, 1), (5, 1), (5, 3), (4, 3), (4, 1), (1, 1), (1, 2)]
    Reciever = [(2, 4), (2, 2), (5, 4)]
    Transmitter = [(4, 4), (6, 3), (6, 2)]
    start = time.perf_counter()
    runSystem(Reciever, Transmitter, Obstruction)
    time1 = time.perf_counter()
    time1 = time1 - start
    print(time1)
    Reciever = [(2, 4), (2, 2), (5, 4), (3, 4)]
    Transmitter = [(4, 4), (6, 3), (6, 2), (7, 4)]
    start = time.perf_counter()
    runSystem(Reciever, Transmitter, Obstruction)
    time2 = time.perf_counter()
    time2 = time2 - start
    print(time2)
    Reciever = [(2, 2), (3, 3), (6, 5), (7, 1), (10, 3)]
    Transmitter = [(2, 5), (4, 5), (5, 5), (9, 2), (8, 1)]
    start = time.perf_counter()
    runSystem(Reciever, Transmitter, Obstruction)
    time3 = time.perf_counter()
    time3 = time3 - start
    print(time3)
    Reciever = [(2, 2), (3, 3), (6, 5), (7, 1), (10, 3), (8, 3)]
    Transmitter = [(2, 5), (4, 5), (5, 5), (9, 2), (8, 1), (7, 4)]
    start = time.perf_counter()
    runSystem(Reciever, Transmitter, Obstruction)
    time4 = time.perf_counter()
    time4 = time4-start
    print(time4)
    Reciever = [(2, 2), (3, 3), (6, 5), (7, 1), (10, 3), (8, 3), (3, 2)]
    Transmitter = [(2, 5), (4, 5), (5, 5), (9, 2), (8, 1), (7, 4), (3, 4)]
    start = time.perf_counter()
    runSystem(Reciever, Transmitter, Obstruction)
    time5 = time.perf_counter()
    time5 = time5 -start
    print(time5)
    Obstruction = [(1, 2), (1, 5), (8, 5), (8, 3), (11, 3), (11, 1), (5, 1), (5, 3), (4, 3), (4, 1), (1, 1), (1, 2)]
    Reciever = [(2, 2), (3, 3), (6, 5), (7, 1), (10, 3), (8, 3), (3, 2), (6, 1)]
    Transmitter = [(2, 5), (4, 5), (5, 5), (9, 2), (8, 1), (7, 4), (3, 4), (9, 1)]
    start = time.perf_counter()
    runSystem(Reciever, Transmitter, Obstruction)
    time6 = time.perf_counter()
    time6 = time6 -start
    print(time6)
    Reciever = [(2, 2), (3, 3), (6, 5), (7, 1), (10, 3), (8, 3), (3, 2), (6, 1), (7, 5)]
    Transmitter = [(2, 5), (4, 5), (5, 5), (9, 2), (8, 1), (7, 4), (3, 4), (9, 1), (3, 1)]
    start = time.perf_counter()
    runSystem(Reciever, Transmitter, Obstruction)
    time7 = time.perf_counter()
    time7 = time7 -start
    print(time7)
    Reciever = [(2, 2), (3, 3), (6, 5), (7, 1), (10, 3), (8, 3), (3, 2), (6, 1), (7, 5), (2, 1)]
    Transmitter = [(2, 5), (4, 5), (5, 5), (9, 2), (8, 1), (7, 4), (3, 4), (9, 1), (3, 1), (10, 1)]
    start = time.perf_counter()
    runSystem(Reciever, Transmitter, Obstruction)
    time8 = time.perf_counter()
    time8 = time8 -start
    print(time8)
    Reciever = [(2, 2), (3, 3), (6, 5), (7, 1), (10, 3), (8, 3), (3, 2), (6, 1), (7, 5), (2, 1), (6, 2)]
    Transmitter = [(2, 5), (4, 5), (5, 5), (9, 2), (8, 1), (7, 4), (3, 4), (9, 1), (3, 1), (10, 1), (8, 2)]
    start = time.perf_counter()
    runSystem(Reciever, Transmitter, Obstruction)
    time9 = time.perf_counter()
    time9 = time9 -start
    print(time9)
    Reciever = [(2, 2), (3, 3), (6, 5), (7, 1), (10, 3), (8, 3), (3, 2), (6, 1), (7, 5), (2, 1), (6, 2), (7, 2)]
    Transmitter = [(2, 5), (4, 5), (5, 5), (9, 2), (8, 1), (7, 4), (3, 4), (9, 1), (3, 1), (10, 1), (8, 2), (2, 3)]
    start = time.perf_counter()
    runSystem(Reciever, Transmitter, Obstruction)
    time10 = time.perf_counter()
    time10 = time10 -start
    print(time10)

#Running tests
test1()
test2()
test3()
test4()
test5()
test6()
test7()
test8()
test9()
test10()
timeTest()