<?php 
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // reCAPTCHA validation
    $recaptchaSecret = '6LfBfHEqAAAAAPDsLtP-8WM5AK37kGgsHEE8OqBB'; // Replace with your secret key
    $recaptchaResponse = $_POST['g-recaptcha-response'];
    $url = 'https://www.google.com/recaptcha/api/siteverify?secret=' . $recaptchaSecret . '&response=' . $recaptchaResponse;

    $response = file_get_contents($url);
    $responseKeys = json_decode($response, true);

    if (intval($responseKeys["success"]) !== 1) {
        echo "Please complete the CAPTCHA.";
    } else {
        // Sanitize and validate form inputs
        $username = htmlspecialchars($_POST['username']);
        $email = filter_var($_POST['email'], FILTER_SANITIZE_EMAIL);
        $password = password_hash($_POST['password'], PASSWORD_DEFAULT);

        // Database connection
        $server = "localhost";
        $user = "root";
        $db_password = ""; // MySQL password, change if necessary
        $database = "login";

        $conn = mysqli_connect($server, $user, $db_password, $database);

        // Check connection
        if (!$conn) {
            die("Connection failed: " . mysqli_connect_error());
        }

        // Insert user data into database
        $sql = "INSERT INTO users (username, email, password) VALUES ('$username', '$email', '$password')";

        if (mysqli_query($conn, $sql)) {
            echo "Registration successful!";
        } else {
            echo "Error: " . $sql . "<br>" . mysqli_error($conn);
        }

        // Close the connection
        mysqli_close($conn);
    }
}
?>
