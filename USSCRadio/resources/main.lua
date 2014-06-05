local eventScene = director:createScene()
local newsScene = director:createScene()
local scheduleScene = director:createScene()
local names = {"news","schedule","events"}

local animateButton = function(event)
   if event.phase == "began" then
      tween:from(button, { xScale=2, yScale=2, time=0.5 })
   end
end

local changeScene = function(event)
	print("something worked")
	if event.phase == "ended" then		
		if director:getCurrentScene() == eventScene then
			director:moveToScene(newsScene,{transitionType="slideInL",transitionTime=0.5})
		elseif director:getCurrentScene() == newsScene then
			director:moveToScene(scheduleScene,{transitionType="slideInL",transitionTime=0.5})
		elseif director:getCurrentScene() == scheduleScene then
			director:moveToScene(eventScene,{transitionType="slideInL",transitionTime=0.5})
	end
	end
end
		
function webViewLoadedEvent(event)
	if (event.type  == "error") then
		print("Error loading web page" .. event.url)
	elseif(event.type == "loaded") then
		print("WebPage Loaded ".. event.url)
	end
end

function eventScene:tearDown(event)
	self.changeButton = self.changeButton:removeFromParent()
	self.button = self.button:removeFromParent()
end
function eventScene:setUp(event)
	self.changeButton = director:createLabel(0,0,"<- EVENTS ->")
	self.changeButton.color = {255,0,0}
	self.button = director:createSprite(0, director.displayCenterY, "textures/HLC.jpg")
	self.button.color = {255,0,0}
	self.button.xScale = .1
	self.button.yScale = .1
	self.button:addEventListener("touch", animateButton)
	self.changeButton:addEventListener("touch",changeScene)
end
eventScene:addEventListener({"setUp", "tearDown"}, eventScene)

function scheduleScene:tearDown(event)
	self.changeButton = self.changeButton:removeFromParent()
	self.button = self.button:removeFromParent()
end
function scheduleScene:setUp(event)
	self.changeButton = director:createLabel(0,0,"<- SCHEDULE ->")
	self.changeButton.color = {0,0,255}
	self.button = director:createSprite(0, director.displayCenterY, "textures/HLC.jpg")
	self.button.color = {0,0,255}
	self.button.xScale = .1
	self.button.yScale = .1
	self.button:addEventListener("touch", animateButton)
	self.changeButton:addEventListener("touch",changeScene)
end
scheduleScene:addEventListener({"setUp", "tearDown"}, scheduleScene)

function newsScene:tearDown(event)
	self.changeButton = self.changeButton:removeFromParent()
	self.button = self.button:removeFromParent()
end
function newsScene:setUp(event)
	self.changeButton = director:createLabel(0,0,"<- NEWS ->")
	self.changeButton.color = {0,255,0}
	self.button = director:createSprite(0, director.displayCenterY, "textures/HLC.jpg")
	self.button.color = {0,255,0}
	self.button.xScale = .1
	self.button.yScale = .1
	self.button:addEventListener("touch", animateButton)
	self.changeButton:addEventListener("touch",changeScene)
end
newsScene:addEventListener({"setUp", "tearDown"}, newsScene)
--system:addEventListener("webViewLoaded",webViewLoadedEvent)
director:moveToScene(eventScene)