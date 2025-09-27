# Individual Test Commands

Here are the PowerShell commands to compile and run each test file individually:

## ArrayList Test
```powershell
# Compile and run
cd "i:\000_HCMUT_CS_2024-2028\001_2ND_YEAR\HK251\DSA\BTL_HCMUT\HCMUT_HK251_FIRST_ASSIGNMENT\the_first_version" ; if ($?) { g++ run_arraylist_test.cpp VectorStore.cpp -o run_arraylist_test -std=c++17 } ; if ($?) { .\run_arraylist_test }
```

## Point Test
```powershell
# Compile and run
cd "i:\000_HCMUT_CS_2024-2028\001_2ND_YEAR\HK251\DSA\BTL_HCMUT\HCMUT_HK251_FIRST_ASSIGNMENT\the_first_version" ; if ($?) { g++ run_point_test.cpp -o run_point_test -std=c++17 } ; if ($?) { .\run_point_test }
```

## SinglyLinkedList Test
```powershell
# Compile and run
cd "i:\000_HCMUT_CS_2024-2028\001_2ND_YEAR\HK251\DSA\BTL_HCMUT\HCMUT_HK251_FIRST_ASSIGNMENT\the_first_version" ; if ($?) { g++ run_singlylinkedlist_test.cpp VectorStore.cpp -o run_singlylinkedlist_test -std=c++17 } ; if ($?) { .\run_singlylinkedlist_test }
```

## VectorStore Test
```powershell
# Compile and run (Note: currently has test failures)
cd "i:\000_HCMUT_CS_2024-2028\001_2ND_YEAR\HK251\DSA\BTL_HCMUT\HCMUT_HK251_FIRST_ASSIGNMENT\the_first_version" ; if ($?) { g++ run_vectorstore_test.cpp VectorStore.cpp -o run_vectorstore_test -std=c++17 } ; if ($?) { .\run_vectorstore_test }
```

## Quick Copy & Paste Commands

**ArrayList:**
```powershell
cd "i:\000_HCMUT_CS_2024-2028\001_2ND_YEAR\HK251\DSA\BTL_HCMUT\HCMUT_HK251_FIRST_ASSIGNMENT\the_first_version" ; if ($?) { g++ run_arraylist_test.cpp VectorStore.cpp -o run_arraylist_test -std=c++17 } ; if ($?) { .\run_arraylist_test }
```

**Point:**
```powershell
cd "i:\000_HCMUT_CS_2024-2028\001_2ND_YEAR\HK251\DSA\BTL_HCMUT\HCMUT_HK251_FIRST_ASSIGNMENT\the_first_version" ; if ($?) { g++ run_point_test.cpp -o run_point_test -std=c++17 } ; if ($?) { .\run_point_test }
```

**SinglyLinkedList:**
```powershell
cd "i:\000_HCMUT_CS_2024-2028\001_2ND_YEAR\HK251\DSA\BTL_HCMUT\HCMUT_HK251_FIRST_ASSIGNMENT\the_first_version" ; if ($?) { g++ run_singlylinkedlist_test.cpp VectorStore.cpp -o run_singlylinkedlist_test -std=c++17 } ; if ($?) { .\run_singlylinkedlist_test }
```

**VectorStore:**
```powershell
cd "i:\000_HCMUT_CS_2024-2028\001_2ND_YEAR\HK251\DSA\BTL_HCMUT\HCMUT_HK251_FIRST_ASSIGNMENT\the_first_version" ; if ($?) { g++ run_vectorstore_test.cpp VectorStore.cpp -o run_vectorstore_test -std=c++17 } ; if ($?) { .\run_vectorstore_test }
```

## Files Created
- `run_arraylist_test.cpp` - ArrayList test runner with main()
- `run_point_test.cpp` - Point test runner with main()
- `run_singlylinkedlist_test.cpp` - SinglyLinkedList test runner with main()
- `run_vectorstore_test.cpp` - VectorStore test runner with main()

## Note
- All tests include proper main() functions for standalone execution
- ArrayList, SinglyLinkedList, and VectorStore tests require VectorStore.cpp
- Point test runs independently
- Using C++17 standard (same as main test file)
- Using PowerShell syntax with `if ($?)` to run executable only if compilation succeeds
- Commands include full path navigation for convenience