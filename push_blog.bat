@echo off
echo "DOCS PUSH BAT"

echo "Start submitting code to the local repository"
git add *
 
echo "Commit the changes to the local repository"
set now=%date% %time%
echo "Time:" %now%
git commit -m "auto push %now%"
 
echo "Push the changes to the remote git server"
git push

echo "Batch execution complete!"
pause