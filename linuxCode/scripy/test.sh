
path="/home/rzk/documents/learning/linux"
echo -n> ${path}/build/temp1
echo -n> ${path}/build/temp2
# sha1sum ${path}/build/copy.pdf > ${path}/build/temp1
# sha1sum ${path}/copy.pdf       > ${path}/build/temp2
# diff ${path}/build/temp1 ${path}/build/temp2

sha1sum  ${path}/build/copy.pdf  ${path}/copy.pdf 
