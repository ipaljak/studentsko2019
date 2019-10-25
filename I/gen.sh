python gen.py

for t in test/*.in.*
do
  ./I < $t > ${t/in/out}
done
