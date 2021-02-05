setInterval(function()
		{
			$(".redsquare2").css(
			{
				"width": involt.pin.A[1]*9.5, 	
			});

			/*---> Plus A1 augmente plus le rectangle augmente*/

			$(".redsquare3").css(
			{
				"width": involt.pin.A[2]*9.5,		
			});

			/*--> Plus A2 augmente plus le rectangle augmente*/
			
			$(".redsquare").css(
			{
				"width": involt.pin.A[3]*9.5,		
			});

			/*---> Plus A3 diminue plus le rectangle diminue*/

			$(".redsquare1").css(
			{
				"width": involt.pin.A[7]*9.5,
			});

			/*---> Plus A7 diminue plus le rectangle diminue*/

			$(".comptearebours").css(
			{
				
				"width": involt.pin.A[6]*3.15,
			});
			/*la largeur du rectangle de la variable rebours sur arduino
			va diminuer toutes les secondes*/
		



if (involt.pin.A[1] > 50)	/*si le nombre de tirs est > 50 alors le rectangle du joueur 1 est rouge*/
{	
	$(".redsquare2").css({

		"background": "red",
	});
}

else if (involt.pin.A[1] > 10) 	/*si le nombre de tirs est > 10 alors le rectangle du joueur 1 est orange*/
{
	$(".redsquare2").css({

		"background": "orange",
	});
}

else 
{
	$(".redsquare2").css({			/*sinon le rectangle du joueur 1 est vert*/

		"background": "green", 
	});
}


if (involt.pin.A[2] > 50) /*si le nombre de tirs est > 50 alors le rectangle du joueur 2 est rouge*/
{	
	$(".redsquare3").css({

		"background": "red",
	});
}

else if (involt.pin.A[2] > 10) /*si le nombre de tirs est > 10 alors le rectangle du joueur 2 est orange*/
{
	$(".redsquare3").css({

		"background": "orange" ,
	});
}

else 
{
	$(".redsquare3").css({	/*sinon le rectangle du joueur 2 est vert*/

		"background": "green",
	});
}

if (involt.pin.A[3] > 50)	/*si le nombre de points de vie est > 50 alors le rectangle du joueur 1 est vert*/
{
	$(".redsquare").css({

		"background": "green",
	});
}

else if (involt.pin.A[3] > 10) /*si le nombre de points de vie est > 10 alors le rectangle du joueur 1 est orange*/
{
	$(".redsquare").css({

		"background": "orange",
	})
}

else
{
	$(".redsquare").css({	/*sinon le rectangle du joueur 1 est rouge*/

		"background":"red",
	})
}

if (involt.pin.A[7] > 50)	/*si le nombre de points de vie est > 50 alors le rectangle du joueur 2 est vert*/
{
	$(".redsquare1").css({

		"background": "green",
	});
}

else if (involt.pin.A[3] > 10) /*si le nombre de points de vie est > 10 alors le rectangle du joueur 2 est orange*/
{
	$(".redsquare1").css({

		"background": "orange",
	})
}

else
{
	$(".redsquare1").css({	/*sinon le rectangle du joueur 1 est rouge*/

		"background":"red",
	})
}


},20);


