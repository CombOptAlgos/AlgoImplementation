# Symplex Algorithm Implementation

## Directory Structure

```
├── __init__.py
├── main.py
├── requirements.txt
├── solvelp.py
└── utils.py
```

## Requirements

```
numpy==1.17.1
```

## Usage

```
>>> import numpy as np
>>> from solvelp import Symplex
>>> A = np.array([
        [1, -1],
        [1, 1],
        [-1, 1],
        [-1, -1]
    ])
>>> b = np.array([1, 1, 1, 1])
>>> c = np.array([[2, -1]])
>>> solver = Symplex().fit(A, b, c)
>>> print(solver.tableau)
[[ 1.   0.   0.5  0.5  0.   0.   1. ]
[ 0.   2.  -1.   1.   0.   0.   0. ]
[ 0.   0.   1.   0.   1.   0.   2. ]
[ 0.   0.   0.   1.   0.   1.   2. ]
[ 0.   0.   1.5  0.5  0.   0.   2. ]]
>>> print(solver.result())
2.0
```

