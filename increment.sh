#!/bin/bash
echo "PRE_BUILD: Adding new build number..."
oldnum=`cut -d ',' -f2 BuildNumberCache.txt`
newnum=`expr $oldnum + 1`
version="0.3 (images)"
apiVersion="4"
echo "$newnum" > BuildNumberCache.txt
echo "#ifndef INCREMENTED_VALUE" > src/misc/increment.hpp
echo "#define INCREMENTED_VALUE" >> src/misc/increment.hpp
echo "" >> src/misc/increment.hpp
echo "#include <string>" >> src/misc/increment.hpp
echo "#include <cstdint>" >> src/misc/increment.hpp
echo "" >> src/misc/increment.hpp
echo "const std::string incrementedVersionValue =  \"$version, build: $newnum (`date +%Y-%m-%d`)\";" >> src/misc/increment.hpp
echo "constexpr uint64_t apiVersion =  $apiVersion;" >> src/misc/increment.hpp
echo "" >> src/misc/increment.hpp
echo "#endif" >> src/misc/increment.hpp
echo "PRE_BUILD: Added new build number: $newnum!"