function Rules ($content, $char) { 
    $sum = 0
    $content | ForEach-Object {
        $password = $_ + $char
        $score = 0
        if ($password -cmatch '[a-z]') { 
            $score++
        }
        
        if ($password -cmatch '[A-Z]') {
            $score++
        }
                
        $flag = $true
        $matches = [regex]::Matches($password, '[0-9]')
        if ($matches.Count -gt 0) {
            $score++
            foreach ($match in $matches) {
                if ($match -match '[012345689]') {
                    $flag = $false
                    break
                }
            }
            
            if ($flag) {
                $score += 7
            }
        }
        
        $matches = [regex]::Matches($password, '(.)\1{2,}')
        if ($matches.Count -gt 0) {
            $longest = $matches | 
                           Sort-Object Length -Descending | 
                           Select-Object -First 1
            $score += $longest.length * $longest.length
        } 
        
        if ($password -cmatch 'red|blue|green') {
            $score *= 3
        }
        
        $sum += $score * $password.length
    }
    
    return $sum
}

$content = Get-Content $args[0]
$chars = @('7', 'd', 'n', 'e')
$max = 0

foreach ($char in $chars) {
    $sum = Rules $content $char
    if ($sum -gt $max) {
        $max = $sum
    }
}

write-host $max