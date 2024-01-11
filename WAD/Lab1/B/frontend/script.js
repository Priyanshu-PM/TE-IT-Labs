function registerUser() {
    // Get user registration data from the form
    const username = document.getElementById("username").value;
    const email = document.getElementById("email").value;
    const password = document.getElementById("password").value;

    // Create an object with the user data
    const userData = {
        username: username,
        email: email,
        password: password
    };

    // Send the user data to the server using AJAX POST request
    $.ajax({
        type: "POST",
        url: "http://localhost:3000/register",
        contentType: "application/json; charset=utf-8",
        data: JSON.stringify(userData),
        success: function(response) {
            // Handle the success response (if needed)
            console.log("User registered successfully");
            console.log("Response is : ", response);
            // Redirect to a new page showing the user list

            document.getElementById("output").innerHTML = "User Registered successfully";
            // window.location.href = "userlist.html";
        },
        error: function(error) {
            // Handle the error response (if needed)
            console.error("Error registering user:", error);
            document.getElementById("output").innerHTML = "Error in registering user";
        }
    });
}
