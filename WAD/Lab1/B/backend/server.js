const express = require('express');
const bodyParser = require('body-parser');

const app = express();
const PORT = 3000;

app.use(bodyParser.json());

// Endpoint to handle user registration
app.post('/register', (req, res) => {
    const userData = req.body;

    // In a real application, you would save this data to a database
    console.log('Received registration data:', userData);

    res.status(200).json({ message: 'User registered successfully' });
});

app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
