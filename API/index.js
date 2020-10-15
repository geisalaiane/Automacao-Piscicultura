const express = require("express")
const cors = require("cors")
const app = express()
const mqtt = require('mqtt')
const client = mqtt.connect('mqtt://test.mosquitto.org')
const router = express.Router()

router.get("/send", async (req, res) => {
  const { message } = req.query

  client.publish('IOTFGFatec/ativacao', message)

  return res.json(message)
})

app.use(cors())
app.use(express.json())
app.use(router)

app.listen(3000, () => console.log('Server started'))
