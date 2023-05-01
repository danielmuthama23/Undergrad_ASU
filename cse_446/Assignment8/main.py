import collections
import json
import logging
import math
import os
import random
import string
import time
from queue import Queue
from threading import Thread, current_thread

OUTPUT_FILE = 'occurrences.json'

# config logger
logging.basicConfig(format='[%(asctime)s]: %(message)s', level=logging.INFO, datefmt='%H:%M:%S')

# the queues to store the produced items for both consumers
reduceQueue = Queue()
combineQueue = Queue()

def Map(inputLines):
    threadName = current_thread().name
    logging.info(f'Starting - {threadName}')

    occurenceDic = collections.defaultdict(int)
    validChars = string.ascii_letters + string.digits

    for line in inputLines:
        line = line.lower()
        words = line.split()
        for word in words:
            cleanedWord = ''.join(c for c in word if c in validChars)
            occurenceDic[cleanedWord] += 1

    # time.sleep(random.randint(1,5))
    reduceQueue.put(occurenceDic)

    logging.info(f'Completed - {threadName}')

def Reduce(isOddConsumer):
    threadName = current_thread().name
    logging.info(f'Starting - {threadName}')

    dicts = [] # hold the two incoming dictionaries

    # consume the first dictionary from the Map thread
    item = reduceQueue.get()
    dicts.append(item)

    # consume the second dictionary from the Map thread if needed
    if not isOddConsumer:
        item = reduceQueue.get()
        dicts.append(item)

    # reduce the 1 or 2 dictionaries
    reducedDict = collections.defaultdict(int)
    for d in dicts:
        for key, value in d.items():
            reducedDict[key] += value

    # once reduced, send to the Combine thread
    combineQueue.put(reducedDict)

    logging.info(f'Completed - {threadName}')

def Combine(numToConsume, results):
    threadName = current_thread().name
    logging.info(f'Starting - {threadName}')

    reducedDictionaries = []

    while len(reducedDictionaries) != numToConsume:
        item = combineQueue.get()
        reducedDictionaries.append(item)

    # combinedDict = collections.defaultdict(int)
    for d in reducedDictionaries:
        for key, value in d.items():
            results[key] += value

    logging.info(f'Completed - {threadName}')

def start_program_with_threads(lines, N):
    # partition data into N independent parts
    numOfLines = len(lines)
    linesPerPartition = math.ceil(numOfLines / N)
    partitions = [lines[i:i+linesPerPartition] for i in range(0, numOfLines, linesPerPartition)]

    threads = []

    # create Map threads
    for i, p in enumerate(partitions):
        t = Thread(target=Map, args=(p,), name=f'Map-{i}')
        threads.append(t)

    # create Reduce threads
    # there will be 1 Reduce thread for every 2 Map threads (sometimes 1 thread when odd)
    numReduceThreads = math.ceil(N / 2)
    for i in range(numReduceThreads):
        # handle if one Reduce thread should only consume 1 item when there is an odd number of items
        isOddConsumer = N % 2 == 1 and i == numReduceThreads - 1
        t = Thread(target=Reduce, args=(isOddConsumer,), name=f'Reduce-{i}')
        threads.append(t)

    combineResults = collections.defaultdict(int)

    # create one Combine thread
    t = Thread(target=Combine, args=(numReduceThreads, combineResults), name=f'Combine')
    threads.append(t)

    # start all threads in the list
    for t in threads:
        t.start()

    # wait for all threads to finish
    for t in threads:
        t.join()

    # sort in descending order of # of occurences
    sortedOccurrences = sorted(combineResults.items(), key=lambda x: x[1], reverse=True)
    sortedDict = dict(sortedOccurrences)

    return sortedDict

if __name__ == '__main__':
    # get the file name input
    fileName = input('\nEnter the name of your data file (must be in current path): ')
    # fileName = 'FileForCounting.txt'
    if not os.path.isfile(fileName):
        print(f'File name {fileName} does not exist...')
        quit()

    # get the input N
    nInput = input('\nEnter N, the number of parallel thread (N >= 1): ')
    N = -1
    try:
        N = int(nInput)
    except ValueError:
        print('N must be a number...')
        quit()
    if N < 1:
        print('N must be >= 1...')
        quit()

    # read the data from the text file
    lines = []
    with open(fileName, encoding='Windows-1252') as f:
        lines = f.readlines()
        f.close()

    # start program with multithreads and calculate execution time
    print('\nStarting multithreaded program:')
    start_time = time.time()
    results_N_threads = start_program_with_threads(lines, N)
    end_time = time.time()
    elapsed_time_N_threads = end_time - start_time

    # start single thread program and calculate execution time
    print('\nStarting single threaded program:')
    start_time = time.time()
    results_single_thread = start_program_with_threads(lines, 1)
    end_time = time.time()
    elapsed_time_single_thread = end_time - start_time

    # write the sorted dictionary to the JSON file
    with open(OUTPUT_FILE, 'w') as f:
        json.dump(results_N_threads, f, indent=4)

    print(f'\nMultithread ({N}) execution time: {elapsed_time_N_threads:.4f} seconds')
    print(f'Single thread execution time: {elapsed_time_single_thread:.4f} seconds')

    print(f'\nProgram output has been saved under {OUTPUT_FILE}\n')