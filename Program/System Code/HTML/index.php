<?php header( "refresh:1" );
$dbname = 'YOUR_DB_NAME';
$dbuser = 'YOUR_DB_USERNAME';  
$dbpass = 'YOUR_PASSWORD'; 
$dbhost = 'localhost'; 

$connect = @mysqli_connect($dbhost,$dbuser,$dbpass,$dbname);

if(!$connect){
	echo "Error: " . mysqli_connect_error();
	exit();
}

// echo "Connection Success!<br><br>";

$moisture = $_GET["moisture"];
$status = $_GET["status"];


$query = "UPDATE moisture SET moisture = ('$moisture'),status = ('$status')";
mysqli_query($connect,$query);

// echo "Insertion Success!<br>";

?>

<html>

<header>
<title> Automated Domestic Irrigation System </title>

<style>
html *
{
   font-family: Arial !important;
   font-size: 5rem;
}
</style

</header>

<body>
    <h1>System Display Interface</h1>

    <?php
    $query2 = "SELECT moisture from moisture";
    $row = mysqli_query($connect,$query2);
    
    while($data = $row->fetch_assoc()){
        if($data["moisture"] > 0){
           echo "<h2 style='color:blue'>Moisture Level: ". $data["moisture"]." Percentage</h2>"; 
        }
    }
    $query3 = "SELECT status from moisture";
    $rows = mysqli_query($connect,$query3);
    
    while($state = $rows->fetch_assoc()){
        
        if( strcmp($state['status'],"ON")  == 0){
            echo "<h2 style='color:green'>Valve Status: ".$state['status'];
        }else if( strcmp($state['status'],"OFF")  == 0 ){
            echo "<h2 style='color:red'>Valve Status: ".$state['status'];
        }
        echo "</h2>";
    }
?> 
</body>
</html>
