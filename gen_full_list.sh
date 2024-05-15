rm full_list
touch full_list

for filename in $(find lib/ -wholename 'lib/*.cpp')
do
    removed_lib=${filename/'lib/'/''}
    echo "${removed_lib//_/-}" $filename >> full_list
done
