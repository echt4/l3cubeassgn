find -not -empty -type f -printf "%s\n" | sort -rn | uniq -d | xargs -I{} -n1 find -type f -size {}c -print0 | xargs -0 md5sum | sort | uniq -w32 --all-repeated=separate>dup_fresh.txt
touch onlyfilename.txt
IFS=" "
while read -r f1 f2
do
	#printf "Field 2=$f2\n"
	if [ -n "$f2" ] 
	then
	base_name=$(basename $f2)
	echo "$f1 $base_name $f2"  >> onlyfilename.txt
	#echo  "$base_name \n"
	fi
done <dup_fresh.txt
echo "Followinf are the file name"
cat onlyfilename.txt
echo "\nEnter the name to delete"
read delete_file
echo "\nYou entered $delete_file"  
cat onlyfilename.txt | awk '{if ($2=="op.txt") print $0;}'>delete_data9.txt
awk -F " " '{print $1}' delete_data9.txt|sort|uniq -d|grep -F -f - delete_data9.txt>final_delete_data.txt
IFS=" "
while read -r t1 t2 t3
do
	echo "$t3"
	rm $t3
done <final_delete_data.txt
echo "Finally,Completed"
echo "BYE"
