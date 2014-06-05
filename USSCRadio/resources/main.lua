local fullScene = director:createScene()
fullScene.newsScene = director:createScene()
fullScene.scheduleScene = director:createScene()
local names = {"news","schedule","events"}
fullScene.newsScene.newsView = nui:createWebView({
	x=0,y=0,w=director.deviceWidth,h=200,transparentBackground=true,
	url="http://radio.uccs.edu",
	} )
fullScene.scheduleScene.scheduleView = nui:createWebView({
	x=0,y=200,w=director.deviceWidth,h=200,transparentBackground=true,
	url="https://www.youtube.com/watch?v=fPevj0vT7-I",
	} )
fullScene.newsScene.newsView.isVisible = true
fullScene.newsScene.zOrder = -1
fullScene.scheduleScene.zOrder = 5
fullScene.label = director:createLabel({text="NEWS",x=500,y=0,w=200,h=100})
fullScene.label.color = {255,0,0}
fullScene.label.zOrder = 2
fullScene.sprite = director:createSprite(40,40,"textures/HLC.jpg");
fullScene.sprite.rotation = -20;
fullScene.sprite.xScale = .1
fullScene.sprite.yScale = .1
fullScene.sprite.color = {255,0,0}
fullScene.sprite.zORder = 3
--[[fullScene.newsView = nui:createWebView({
	x=0,y=yStart,w=director.displayWidth,h=height,transparentBackground=true,
	url="http://radio.uccs.edu",
	} )
	
fullScene.scheduleView = nui:createWebView({
	x=0,y=0,w=director.displayWidth,h=director.isplayHeight,transparentBackground=true,isVisible=false,
	url="http://radio.uccs.edu/index.php/schedule",
	} )
]]



function webViewLoadedEvent(event)
	if (event.type  == "error") then
		print("Error loading web page" .. event.url)
	elseif(event.type == "loaded") then
		print("WebPage Loaded ".. event.url)
	end
end

system:addEventListener("webViewLoaded",webViewLoadedEvent)