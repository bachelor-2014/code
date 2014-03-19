# Splotbot logging

## Functionality

- We store data in scope of a identifier. Intuitively this could for v1
be "experiment1...N". Maybe we need some kind of count
- This leaves room for the implementation to specify granularity (eg. 
"experiment1-0-15m", etc.
- Data will be retrievable in a single BLOB. This makes it easy to get
a common interface between files, videos and DB. Technically it should
be easy to extend eg. a relational DB writer to have higher
granularity as it will probably be saved with a composite key like:
(identifier,inc-id)

## Design

One class (logger.h) defines in/out functionality
of subclasses (kvlogger.cpp,dblogger.cpp,filelogger.cpp,videologger.cpp)

- Start
    - Opens a new ressource with some form of identifier
- End
    - Closes the open ressource
- Write
    - Appends to the open ressource
- Read
    - Retrieves and entire BLOB of data based on identifier
