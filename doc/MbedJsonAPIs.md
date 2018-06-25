基于ARM OS的第三方json开源api
Types Abstraction. Minimalist JSON serializer and parser (inspired by picojson). Is used by MbedJSONRpc.
/** MbedJSONValue class
 *
 * Example:
 *    - creation of an MbedJSONValue of type TypeObject containing two others MbedJSONValue: 
 *         -one array of one string and one integer identified by "my_array"
 *         -a boolean identified by "my_boolean"
 *    - serialization in JSON format of this object
 * @code
 * #include "mbed.h"
 * #include "MbedJSONValue.h"
 * #include <string>
 *
 * int main() {          
 *
 *   MbedJSONValue demo;
 *   std::string s;
 *
 *   //fill the object
 *   demo["my_array"][0] = "demo_string";
 *   demo["my_array"][1] = 10;
 *   demo["my_boolean"] = false;
 *
 *   //serialize it into a JSON string
 *   s = demo.serialize();
 *   printf("json: %s\r\n", s.c_str());
 * }
 *  
 * @endcode
 *
 * Example:
 *     - creation of an MbedJSONValue from a JSON string
 *     - extraction of different values from this existing MbedJSONValue
 * @code
 * #include "mbed.h"
 * #include "MbedJSONValue.h"
 * #include <string>
 *
 * int main() {     
 *    MbedJSONValue demo;
 *
 *   const  char * json = "{\"my_array\": [\"demo_string\", 10], \"my_boolean\": true}";
 *
 *   //parse the previous string and fill the object demo
 *   parse(demo, json);
 *
 *   std::string my_str;
 *   int my_int;
 *   bool my_bool;
 *
 *   my_str = demo["my_array"][0].get<std::string>();
 *   my_int = demo["my_array"][1].get<int>();
 *   my_bool = demo["my_boolean"].get<bool>();
 *   
 *    printf("my_str: %s\r\n", my_str.c_str());
 *    printf("my_int: %d\r\n", my_int);
 *    printf("my_bool: %s\r\n", my_bool ? "true" : "false");
 * }
 * @endcode
 */