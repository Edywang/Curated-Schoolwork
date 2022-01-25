class Cache(object):

    def __init__(self):
        self.d = {}

    def set(self, k, v):
        """Sets the key k to value v in the cache."""
        self.d[k] = v

    def get(self, k):
        """Gets the value of key k from the cache, or None if the
        key is not present."""
        return self.d.get(k)

    def remove(self, k):
        """Removes key k from the cache."""
        if k in self.d:
            del self.d[k]

    def len(self):
        return len(self.d)

### OrderedCache

class OrderedCache(Cache):

    def __init__(self):
        super().__init__()
        # 1 line
        # YOUR CODE HERE
        self.keyList = []
        # YOUR CODE ENDS HERE

    def _accessed(self, k):
        """This function notes that the key k has been accessed.
        NOTE: A key counts as accessed only if it actually is in
        the dictionary, not if someone tries to get its value, but
        it does not belong to the dictionary!
        """
        # 4 lines
        # YOUR CODE HERE
        if(k in self.keyList):
          self.keyList.remove(k)
        if(super().get(k) is not None):
          self.keyList.append(k)
        # YOUR CODE ENDS HERE

    def set(self, k, v):
        super().set(k, v)
        self._accessed(k)

    def get(self, k):
        self._accessed(k)
        return super().get(k)

    def remove(self, k):
        """We remove the key from the list of keys before calling
        super().remove"""
        # Remove k from the key list, if present.
        # 2 lines
        # YOUR CODE HERE
        if(k in self.keyList):
          self.keyList.remove(k)
        # YOUR CODE ENDS HERE
        super().remove(k)

    def len(self, k):
        return len(self.d)

    @property
    def oldest_key(self):
        """Returns the oldest accessed key, or None if no key has ever been
        accessed."""
        # 1 line
        # YOUR CODE HERE.
        return self.keyList[0]
        # YOUR CODE ENDS HERE

    @property
    def newest_key(self):
        """Returns the most newly accessed key, or None if no key has ever
        been accessed."""
        # 1 line
        # YOUR CODE HERE
        return self.keyList[-1]
        # YOUR CODE ENDS HERE


### Here are some tests (10 points)

c = OrderedCache()

c.set('a', 2)
c.set('b', 3)
assert c.oldest_key == 'a'
assert c.newest_key == 'b'

# If we access 'c', which does not exist, the newest key is still b.
assert c.get('c') == None
assert c.oldest_key == 'a'
assert c.newest_key == 'b'

# This works also for keys that are not strings...
c.set(5, 6)
assert c.newest_key == 5

### Some more tests (10 points)

# If we now access 'a', then it becomes the newest key.
assert c.get('a') == 2
assert c.oldest_key == 'b'
assert c.newest_key == 'a'

### BoundedCache

class BoundedCache(OrderedCache):

    def __init__(self, size_limit=4):
        """Creates a bounded cache with a given size limit.
        If more than size_limit elements are added, the oldest-accessed
        elements are deleted from the cache."""
        super().__init__()
        self.size_limit = size_limit

    def set(self, k, v):
        """Sets key k to map to element v.
        If k is already in the cache, the mapping should be simply updated.
        If k is not in the cache, and the cache already
        has reached maximum size, deletes the oldest accessed mapping
        before adding the k:v one."""
        # 3 lines
        # YOUR CODE HERE
        if(super().get(k) is None and super().len(k) == self.size_limit):
            super().remove(super().oldest_key)
        super().set(k, v)
        # YOUR CODE ENDS HERE

### Some tests for bounded cache (10 points)

c = BoundedCache(2)
c.set('a', 1)
c.set('b', 2)
c.set('c', 3)
assert c.get('a') == None
assert c.get('b') == 2

c = BoundedCache(3)
c.set('a', 1)
c.set('b', 2)
c.set('c', 3)
c.get('a')
c.set('d', 4)
assert c.get('a') == 1
assert c.get('b') == None

c = BoundedCache(3)
c.set(1, 1)
c.set(2, 2)
c.set(3, 3)
c.get(1)
c.set(4, 4)
c.set(5, 5)
assert c.get(4) == 4
assert c.get(3) == None
assert c.get(1) == 1
assert c.get(2) == None