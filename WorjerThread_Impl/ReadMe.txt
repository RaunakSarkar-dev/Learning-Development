Worker threads are threads which are conceptually used to delegate the tasks that needs to be run periodically 
and for which the main thread should not be blocked. It can also be used to carry out tasks which are time consuming
or involves heavy operations like reading large data from Databases. if done so, the main thread delegates the
responsibility of reading data to a worker thread asynchronously and carry on with its activities, without bothering
about the read operation and only start processing the data once it receives the data back from worker thread.
