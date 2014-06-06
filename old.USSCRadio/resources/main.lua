local eventScene = director:createScene()
local newsScene = director:createScene()
local scheduleScene = director:createScene()
local names = {"news","schedule","events"}
local touchX = 0;

local changeSceneLeft = function()
	if director:getCurrentScene() == eventScene then
		--director:moveToScene(newsScene,{transitionType="slideInL",transitionTime=0.5})
	elseif director:getCurrentScene() == newsScene then
		director:moveToScene(eventScene,{transitionType="slideInL",transitionTime=0.5})
	elseif director:getCurrentScene() == scheduleScene then
		director:moveToScene(newsScene,{transitionType="slideInL",transitionTime=0.5})
	end
end

local changeSceneRight = function()
	if director:getCurrentScene() == eventScene then
		director:moveToScene(newsScene,{transitionType="slideInR",transitionTime=0.5})
	elseif director:getCurrentScene() == newsScene then
		director:moveToScene(scheduleScene,{transitionType="slideInR",transitionTime=0.5})
	elseif director:getCurrentScene() == scheduleScene then
		--director:moveToScene(newsScene,{transitionType="slideInR",transitionTime=0.5})
	end
end

local swipeEvent = function(event)
	if event.phase == "began" then
		touchX = event.x
	elseif event.phase == "moved" then
		if touchX-event.x >10 then
			changeSceneRight()
		elseif touchX-event.x < -10 then
			changeSceneLeft()
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
	self.changeButton = director:createLabel(0,director.displayHeight-50,"<- EVENTS ->")
	self.changeButton.color = color.white
	self.button = director:createSprite(0, director.displayCenterY, "textures/HLC.jpg")
	self.button.color = {255,0,0}
	self.button.xScale = .1
	self.button.yScale = .1
end
eventScene:addEventListener({"setUp", "tearDown"}, eventScene)

function scheduleScene:tearDown(event)
	self.changeButton = self.changeButton:removeFromParent()
	self.button = self.button:removeFromParent()
end
function scheduleScene:setUp(event)
	self.changeButton = director:createLabel(0,director.displayHeight-50,"<- SCHEDULE ->")
	self.changeButton.color = color.white
	self.button = director:createSprite(0, director.displayCenterY, "textures/HLC.jpg")
	self.button.color = {0,0,255}
	self.button.xScale = .1
	self.button.yScale = .1
end
scheduleScene:addEventListener({"setUp", "tearDown"}, scheduleScene)

function newsScene:tearDown(event)
	self.changeButton = self.changeButton:removeFromParent()
	self.button = self.button:removeFromParent()
end
function newsScene:setUp(event)
	self.changeButton = director:createLabel(0,director.displayHeight-50,"<- NEWS ->")
	self.changeButton.color = color.white
	self.button = director:createSprite(0, director.displayCenterY, "textures/HLC.jpg")
	self.button.color = {0,255,0}
	self.button.xScale = .1
	self.button.yScale = .1
end
newsScene:addEventListener({"setUp", "tearDown"}, newsScene)
system:addEventListener("webViewLoaded",webViewLoadedEvent)
system:addEventListener("touch",swipeEvent)
director:moveToScene(newsScene)