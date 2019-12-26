$CurrentPath=$env:Path
$CurrentPath = ($CurrentPath.Split(';') | Where-Object { $_ -ne 'C:/Users/User/AppData/Local/Atlassian/SourceTree/git_local/bin/' }) -join ';'
Write-Output $CurrentPath
cmake -G"MinGW Makefiles" . 