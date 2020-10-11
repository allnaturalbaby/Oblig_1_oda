#! /bin/bash

while read -r userid
do
	curl -k -s https://web01.usn.no/~$(printf "$userid" | tr -d s)/pub_key.asc |
	grep -q "404 Not Found" && printf "0 " || printf "1 "
	grep "$userid" /etc/passwd | cut -f5 -d: | tr -d ,
done < <(members da-oda2001-2020 | tr " " "\n")
