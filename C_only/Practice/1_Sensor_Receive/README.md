Problem: Sensor Data Processing
 
There are 3 types of sensors: A, B, and C. The raw data received from all these sensors is 4 bytes in size, but the data type differs for each sensor as follows:
 
- Sensor A: Data type is `int` (4 bytes).  
- Sensor B: Data type is `float` (4 bytes).  
- Sensor C: Data type is `unsigned int` (4 bytes).  
 
To process the raw data, a calculation must be applied to filter and compute the `value` for each sensor type according to the following formulas:
 
- Sensor A: `value = (raw - 20) / 2`  
- Sensor B: `value = (raw + 10) / 3`  
- Sensor C: `value = (raw + 15.6) / 2.3`  
 
### Requirements:
 
1. Define a unified `struct` to represent a sensor: 
   - It should include an ID to distinguish the sensor type (e.g., `ID = 1` corresponds to Sensor A).  
   - A data `struct` that describes the 'raw' data and 'values' of all 3 sensor types.  
	  For example: Sensor B has 4 bytes of raw data: `0x5B 0x01 0x00 0x00`, which represents the value 347 in little-endian format.
   - A function pointer to handle data processing specific to each sensor type.  
 
2. Write data processing functions:  
   Create functions for processing raw data depending on the sensor type. These functions should be callable via the function pointer in the `struct`.
 
3. Analyze and display sensors with the same raw values:  
   Given a mixed array of sensors with the format:  
   ```
   { {ID, Data struct, ...}, {ID, Data struct, ...}, ... }
   ```
   Display information about the number of sensors of the same type that share the same raw value. For example:  
 
   **Input:**  
   ```
   { {1, {20, [14 00 00 00]}, ...}, {2, {20, [14 00 00 00]}, ...}, {3, {10.3, [CD CC 2C 41]}, ...}, {1, {20, [14 00 00 00]}, ...}, {3, {10.3, [CD CC 2C 41] }, ...} }
   ```
 
   Output (Display):
   ```
   - Sensor type A (ID = 1): There are 2 sensors with the raw value of 20.  
   - Sensor type C (ID = 3): There are 2 sensors with the raw value of 10.3.  
   
   






