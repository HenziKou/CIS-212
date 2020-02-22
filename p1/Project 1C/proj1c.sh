#!/bin/bash

# Format:
#   Username: password(*): User ID: Group ID: Full name: home directory: login shell
#
# Example:
#   nobody:*:-2:-2:Unprivileged User:/var/empty:/user/bin/false

# Header of the file
cat passwd_212 | head -n 18 > passwd_212_no90s

# PART A:
num_users=$(cat passwd_212 | wc -l)
(( num_users = num_users + 1 ))
X=19

while (( X < $num_users )) ; do
   line=$(cat passwd_212 | head -n $X | tail -n 1)
   userID=$(echo $line | cut -d':' -f3)
   userID=$(echo $userID)

   if [[ $userID < 91 ]] ; then
      echo $line >> passwd_212_no90s
   fi

  (( X += 1 ))
done


# PART B:
cat passwd_212_no90s | cut -d':' -f7 | grep -v '^#' | sort | uniq -c | grep /

# To get rid of whitespace pipe the output to "grep /"
# To get rid of comments also pipe the output to "grep -v"
