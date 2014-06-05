local fullScene = director:createScene()
local names = {"news","schedue","events"}
fullScene.label = director:createLabel(director.displayHeight,0,"NEWS")
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