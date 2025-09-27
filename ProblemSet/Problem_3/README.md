# **3️⃣ Caching**

Problem:

Implement a Simple LRU (Least Recently Used) Cache for key-value pairs.

- API: get(key), put(key, value).
- If cache is full, the least recently used entry is evicted.
- Use RAII to ensure resources stored in cache (e.g., heap objects) are automatically released when evicted.

👉 Stretch goal: Make the cache thread-safe.

