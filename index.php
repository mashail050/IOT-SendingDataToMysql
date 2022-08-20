<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <title></title>
  </head>
  <body style="background-color:#4682B4;">
    <h1 style="position:relative; left:260px; top:200px;">This WebPage to get the DHT11 sensor values and store it in a database</h1>

    <?php
    class dht11{
    public $link='';
    function __construct($temperature, $humidity){
    $this->connect();
    $this->storeInDB($temperature, $humidity);
    }
    // function to connect php with mysql
    function connect(){
    $this->link = mysqli_connect('localhost','root','') or die('Cannot connect to the DB');
    mysqli_select_db($this->link,'sensors') or die('Cannot select the DB');//*note sensors is the database name in mysql you can write any name
    }
    // function to store values in database
    function store($temperature, $humidity){
    $query = "insert into sensor set humidity='".$humidity."', temperature='".$temperature."'";//*note sensor is the table name in mysql you can write any name
    $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
    }
    }//end of the class

    if(isset($temperature) || isset($humidity)){
    if($_GET['temperature'] != '' and  $_GET['humidity'] != ''){
    $dht11 = new dht11($_GET['temperature'],$_GET['humidity']);
    }
    }
    else{

    }

     ?>
  </body>
</html>
