# **🔹 Problem: Safe File Logger**

You’re building a Logger class that writes logs to a file.

- Each time a log message is written, the file should be opened, written to, and safely closed (even if exceptions occur).
- Multiple parts of your code should be able to call the logger without worrying about forgetting to close the file.
- The logger should use RAII to manage the file resource.

# **Requirements:**

1. Implement a Logger class that:
    - Opens a file in the constructor.
    - Provides a log(const std::string&) method to append messages.
    - Automatically closes the file in the destructor.
2. Make sure no resource leaks occur if an exception happens while writing.
3. Demonstrate usage in main() by writing multiple log messages.


# **Idea:**
LogManager:
    - Log Configuration: 
      - Log name
      - Log level
    - Log Mechanism
      - Open
      - Close
      - Write
    - Singleton
    - Access from multiple thread

