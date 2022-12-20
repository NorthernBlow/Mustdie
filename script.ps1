$ShortcutsDir = $PSScriptRoot

Write-Host $PSScriptRoot

Get-Childitem -Path $ShortcutsDir -Recurse


function Get-DesktopShortcuts{

    $Shortcuts = Get-ChildItem -Recurse $ShortcutsDir -Include *.lnk -Force
    Write-Host "Всего найдено ярлыков:" $Shortcuts.Count -ForegroundColor Green

    ForEach ($Shortcut in $Shortcuts) {

        $ShortcutObj =$null
        $Destination = $Shortcut.FullName
        $Shell = New-Object -COM WScript.Shell

        $ShortcutObj = $Shell.CreateShortcut($Destination)

        $Path = $ShortcutObj.TargetPath
        $NewPath = $ShortcutsDir
        Move-Item -Path $Path -Destination $NewPath

        #Write-Host $Shell.CurrentDirectory

    }





    
    # Where-Object -FilterScript { $_.ShortcutsDir -like ".lnk" }














}

Get-DesktopShortcuts