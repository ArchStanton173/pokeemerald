DewfordTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordTown_OnTransition
	.byte 0

DewfordTown_OnTransition:
	setflag FLAG_VISITED_DEWFORD_TOWN
	end

DewfordTown_EventScript_Briney::
	lock
	faceplayer
	goto_if_unset FLAG_DELIVERED_STEVEN_LETTER, DewfordTown_EventScript_ReturnToPetalburgPrompt
	message DewfordTown_Text_WhereAreWeBound
	waitmessage
	multichoicedefault 21, 6, MULTI_BRINEY_ON_DEWFORD, 2, FALSE
	switch VAR_RESULT
	case 0, DewfordTown_EventScript_ChoosePetalburg
	case 1, DewfordTown_EventScript_ChooseSlateport
	case 2, DewfordTown_EventScript_CancelSailSelect
	case MULTI_B_PRESSED, DewfordTown_EventScript_CancelSailSelect
	end

DewfordTown_EventScript_ChoosePetalburg::
	msgbox DewfordTown_Text_PetalburgWereSettingSail, MSGBOX_DEFAULT
	closemessage
	goto DewfordTown_EventScript_SailToPetalburg
	release
	end

DewfordTown_EventScript_ChooseSlateport::
	msgbox DewfordTown_Text_SlateportWereSettingSail, MSGBOX_DEFAULT
	closemessage
	goto DewfordTown_EventScript_SailToSlateport
	release
	end

DewfordTown_EventScript_CancelSailSelect::
	msgbox DewfordTown_Text_JustTellMeWhenYouNeedToSetSail, MSGBOX_DEFAULT
	closemessage
	release
	end

DewfordTown_EventScript_ReturnToPetalburgPrompt::
	msgbox DewfordTown_Text_SetSailBackToPetalburg, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, DewfordTown_EventScript_SailBackToPetalburg
	msgbox DewfordTown_Text_GoDeliverIllBeWaiting, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_SailBackToPetalburg::
	msgbox DewfordTown_Text_PetalburgWereSettingSail2, MSGBOX_DEFAULT
	closemessage
	goto DewfordTown_EventScript_SailToPetalburg
	end

DewfordTown_EventScript_Woman::
	msgbox DewfordTown_Text_TinyIslandCommunity, MSGBOX_NPC
	end

DewfordTown_EventScript_MagikarpSalesman::
    lock
    faceplayer
    goto_if_set FLAG_BOUGHT_DEWFORD_MAGIKARP, DewfordTown_EventScript_MagikarpAlreadyBought
    checkplayergender
    goto_if_eq VAR_RESULT, MALE, DewfordTown_EventScript_MagikarpOfferBoy
    goto DewfordTown_EventScript_MagikarpOfferGirl

DewfordTown_EventScript_MagikarpOfferBoy::
    msgbox Dewford_Text_XavierBuyMagikarpForJust500, MSGBOX_DEFAULT
    goto DewfordTown_EventScript_MagikarpAsk

DewfordTown_EventScript_MagikarpOfferGirl::
    msgbox Dewford_Text_HailanBuyMagikarpForJust500, MSGBOX_DEFAULT
    goto DewfordTown_EventScript_MagikarpAsk

DewfordTown_EventScript_MagikarpAsk::
    msgbox DewfordTown_Text_MagikarpConfirm, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, DewfordTown_EventScript_MagikarpDeclined
    checkmoney 500
    goto_if_eq VAR_RESULT, FALSE, DewfordTown_EventScript_MagikarpNoMoney

    setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_MAGIKARP
    givemon SPECIES_MAGIKARP, 5
    goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, DewfordTown_EventScript_MagikarpSuccess
    goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, DewfordTown_EventScript_MagikarpSuccessPC
    goto DewfordTown_EventScript_MagikarpNoRoom

DewfordTown_EventScript_MagikarpSuccess::
    removemoney 500
    setflag FLAG_BOUGHT_DEWFORD_MAGIKARP

    playfanfare MUS_OBTAIN_ITEM
    message DewfordTown_Text_ReceivedMagikarp
    waitfanfare
    waitmessage

    bufferspeciesname STR_VAR_1, SPECIES_MAGIKARP
    msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, DewfordTown_EventScript_MagikarpFinish

    call Common_EventScript_GetGiftMonPartySlot
    call Common_EventScript_NameReceivedPartyMon
    goto DewfordTown_EventScript_MagikarpFinish

DewfordTown_EventScript_MagikarpSuccessPC::
    removemoney 500
    setflag FLAG_BOUGHT_DEWFORD_MAGIKARP

    playfanfare MUS_OBTAIN_ITEM
    message DewfordTown_Text_ReceivedMagikarp
    waitfanfare
    waitmessage

    goto DewfordTown_EventScript_MagikarpFinish

DewfordTown_EventScript_MagikarpFinish::
    msgbox DewfordTown_Text_MagikarpPurchased, MSGBOX_DEFAULT
    release
    end

    playfanfare MUS_OBTAIN_ITEM
    message DewfordTown_Text_ReceivedMagikarp
    waitfanfare
    waitmessage

    msgbox DewfordTown_Text_MagikarpPurchased, MSGBOX_DEFAULT
    release
    end

DewfordTown_EventScript_MagikarpDeclined::
    msgbox DewfordTown_Text_MagikarpDeclined, MSGBOX_DEFAULT
    release
    end

DewfordTown_EventScript_MagikarpNoMoney::
    msgbox DewfordTown_Text_MagikarpNoMoney, MSGBOX_DEFAULT
    release
    end

DewfordTown_EventScript_MagikarpNoRoom::
    msgbox DewfordTown_Text_MagikarpNoRoom, MSGBOX_DEFAULT
    release
    end

DewfordTown_EventScript_MagikarpAlreadyBought::
    msgbox DewfordTown_Text_MagikarpAlreadyBought, MSGBOX_DEFAULT
    release
    end

DewfordTown_EventScript_TownSign::
	msgbox DewfordTown_Text_TownSign, MSGBOX_SIGN
	end

DewfordTown_EventScript_GymSign::
	msgbox DewfordTown_Text_GymSign, MSGBOX_SIGN
	end

DewfordTown_EventScript_HallSign::
	msgbox DewfordTown_Text_HallSign, MSGBOX_SIGN
	end

DewfordTown_EventScript_OldRodFisherman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_OLD_ROD, DewfordTown_EventScript_HowsFishing
	msgbox DewfordTown_Text_GettingItchToFish, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, DewfordTown_EventScript_GiveOldRod
	goto_if_eq VAR_RESULT, NO, DewfordTown_EventScript_NotGettingItchToFish
	end

DewfordTown_EventScript_GiveOldRod::
	msgbox DewfordTown_Text_GiveYouOneOfMyRods, MSGBOX_DEFAULT
	giveitem ITEM_OLD_ROD
	setflag FLAG_RECEIVED_OLD_ROD
	msgbox DewfordTown_Text_ThrowInFishingAdvice, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_NotGettingItchToFish::
	msgbox DewfordTown_Text_ThatsTooBadThen, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_HowsFishing::
	message DewfordTown_Text_HowsYourFishing
	waitmessage
	multichoice 20, 8, MULTI_HOWS_FISHING, TRUE
	goto_if_eq VAR_RESULT, 0, DewfordTown_EventScript_FishingExcellent
	goto_if_eq VAR_RESULT, 1, DewfordTown_EventScript_FishingNotSoGood
	end

DewfordTown_EventScript_FishingExcellent::
	msgbox DewfordTown_Text_GreatHaulInSomeBigOnes, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_FishingNotSoGood::
	msgbox DewfordTown_Text_FishingAdvice, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_SailToPetalburg::
	call EventScript_BackupMrBrineyLocation
	setobjectsubpriority LOCALID_DEWFORD_BRINEY, MAP_DEWFORD_TOWN, 0
	setobjectsubpriority LOCALID_PLAYER, MAP_DEWFORD_TOWN, 0
	applywaitmovement LOCALID_DEWFORD_BRINEY, DewfordTown_Movement_BrineyBoardBoat
	removeobject LOCALID_DEWFORD_BRINEY
	applywaitmovement LOCALID_PLAYER, DewfordTown_Movement_PlayerBoardBoat
	hideobjectat LOCALID_PLAYER, MAP_DEWFORD_TOWN
	call Common_EventScript_PlayBrineysBoatMusic
	applymovement LOCALID_DEWFORD_BOAT, DewfordTown_Movement_SailToPetalburg
	applymovement LOCALID_PLAYER, DewfordTown_Movement_SailToPetalburg
	waitmovement 0
	showobjectat LOCALID_PLAYER, MAP_ROUTE104
	call Common_EventScript_StopBrineysBoatMusic
	applywaitmovement LOCALID_PLAYER, DewfordTown_Movement_ExitBoatPetalburg
	showobjectat LOCALID_PLAYER, MAP_ROUTE104
	clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	clearflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	setflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	hideobjectat LOCALID_DEWFORD_BOAT, MAP_DEWFORD_TOWN
	setvar VAR_BOARD_BRINEY_BOAT_STATE, 2
	resetobjectsubpriority LOCALID_PLAYER, MAP_DEWFORD_TOWN
	warp MAP_ROUTE104_MR_BRINEYS_HOUSE, 5, 4
	copyvar VAR_BRINEY_LOCATION, VAR_0x8008
	waitstate
	release
	end

DewfordTown_EventScript_SailToSlateport::
	call EventScript_BackupMrBrineyLocation
	setobjectsubpriority LOCALID_DEWFORD_BRINEY, MAP_DEWFORD_TOWN, 0
	setobjectsubpriority LOCALID_PLAYER, MAP_DEWFORD_TOWN, 1
	applywaitmovement LOCALID_DEWFORD_BRINEY, DewfordTown_Movement_BrineyBoardBoat
	removeobject LOCALID_DEWFORD_BRINEY
	applywaitmovement LOCALID_PLAYER, DewfordTown_Movement_PlayerBoardBoat
	hideobjectat LOCALID_PLAYER, MAP_DEWFORD_TOWN
	call Common_EventScript_PlayBrineysBoatMusic
	applymovement LOCALID_DEWFORD_BOAT, DewfordTown_Movement_SailToSlateport
	applymovement LOCALID_PLAYER, DewfordTown_Movement_SailToSlateport
	waitmovement 0
	call Common_EventScript_StopBrineysBoatMusic
	showobjectat LOCALID_PLAYER, MAP_ROUTE109
	applywaitmovement LOCALID_PLAYER, DewfordTown_Movement_ExitBoatSlateport
	setobjectxyperm LOCALID_ROUTE109_BRINEY, 21, 26
	addobject LOCALID_ROUTE109_BRINEY
	setobjectsubpriority LOCALID_ROUTE109_BRINEY, MAP_ROUTE109, 0
	applywaitmovement LOCALID_ROUTE109_BRINEY, DewfordTown_Movement_BrineyExitBoat
	clearflag FLAG_HIDE_ROUTE_109_MR_BRINEY
	addobject LOCALID_ROUTE109_BOAT
	clearflag FLAG_HIDE_ROUTE_109_MR_BRINEY_BOAT
	setflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	hideobjectat LOCALID_DEWFORD_BOAT, MAP_DEWFORD_TOWN
	call_if_unset FLAG_DELIVERED_DEVON_GOODS, DewfordTown_EventScript_LandedSlateportDeliverGoods
	call_if_set FLAG_DELIVERED_DEVON_GOODS, DewfordTown_EventScript_LandedSlateport
	closemessage
	copyvar VAR_BRINEY_LOCATION, VAR_0x8008
	resetobjectsubpriority LOCALID_PLAYER, MAP_DEWFORD_TOWN
	resetobjectsubpriority LOCALID_ROUTE109_BRINEY, MAP_ROUTE109
	copyobjectxytoperm LOCALID_ROUTE109_BRINEY
	release
	end

DewfordTown_EventScript_LandedSlateportDeliverGoods::
	msgbox DewfordTown_Text_BrineyLandedInSlateportDeliverGoods, MSGBOX_DEFAULT
	return

DewfordTown_EventScript_LandedSlateport::
	msgbox DewfordTown_Text_BrineyLandedInSlateport, MSGBOX_DEFAULT
	return

DewfordTown_Movement_SailToPetalburg:
	walk_up
	walk_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DewfordTown_Movement_SailToSlateport:
	walk_right
	walk_fast_right
	walk_fast_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

DewfordTown_Movement_PlayerBoardBoat:
	walk_right
	walk_up
	step_end

DewfordTown_Movement_ExitBoatPetalburg:
	walk_up
	walk_up
	walk_up
	step_end

DewfordTown_Movement_ExitBoatSlateport:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

DewfordTown_Movement_BrineyBoardBoat:
	walk_up
	step_end

DewfordTown_Movement_BrineyExitBoat:
	walk_up
	walk_up
	step_end

DewfordTown_EventScript_TrendyPhraseBoy::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Text_XIsTheBiggestHappeningThingRight, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, DewfordTown_EventScript_ConfirmTrendyPhrase
	goto_if_eq VAR_RESULT, NO, DewfordTown_EventScript_RejectTrendyPhrase
	end

DewfordTown_EventScript_ConfirmTrendyPhrase::
	msgbox DewfordTown_Text_YeahDefinitionOfInRightNow, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_RejectTrendyPhrase::
	msgbox DewfordTown_Text_TellMeWhatsNewAndIn, MSGBOX_DEFAULT
	setvar VAR_0x8004, EASY_CHAT_TYPE_TRENDY_PHRASE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_EventScript_GiveNewTrendyPhrase
	goto_if_eq VAR_RESULT, FALSE, DewfordTown_EventScript_CancelNewTrendyPhrase
	end

DewfordTown_EventScript_GiveNewTrendyPhrase::
	incrementgamestat GAME_STAT_STARTED_TRENDS
	goto_if_eq VAR_0x8004, FALSE, DewfordTown_EventScript_PhraseNotTrendyEnough
	msgbox DewfordTown_Text_OfCourseIKnowAboutThat, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_CancelNewTrendyPhrase::
	msgbox DewfordTown_Text_HearOfAnyTrendsComeShareWithMe, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_PhraseNotTrendyEnough::
	msgbox DewfordTown_Text_XHuhIThinkYIsCool, MSGBOX_DEFAULT
	release
	end

DewfordTown_Text_TinyIslandCommunity:
	.string "DEWFORD is a tiny island community.\n"
	.string "If something gets trendy here,\l"
	.string "everyone picks up on it right away.$"

DewfordTown_Text_TownSign:
	.string "DEWFORD TOWN\n"
	.string "“A tiny island in the blue sea.”$"

DewfordTown_Text_GymSign:
	.string "DEWFORD TOWN POKéMON GYM\n"
	.string "LEADER: BRAWLY\l"
	.string "“A big wave in fighting!”$"

DewfordTown_Text_HallSign:
	.string "DEWFORD HALL\n"
	.string "“Everyone's information exchange!”$"

Route104_Text_LandedInDewfordDeliverLetter:
	.string "MR. BRINEY: Ahoy!\n"
	.string "We've hit land in DEWFORD.\p"
	.string "I suppose you're off to deliver that\n"
	.string "LETTER to, who was it now, STEVEN!$"

DewfordTown_Text_SetSailBackToPetalburg:
	.string "MR. BRINEY: Have you delivered your\n"
	.string "LETTER?\p"
	.string "Or were you meaning to sail back to\n"
	.string "PETALBURG?$"

DewfordTown_Text_PetalburgWereSettingSail2:
	.string "MR. BRINEY: PETALBURG it is, then!\p"
	.string "Anchors aweigh!\n"
	.string "PEEKO, we're setting sail, my darling!$"

DewfordTown_Text_GoDeliverIllBeWaiting:
	.string "MR. BRINEY: Then you go on and deliver\n"
	.string "the LETTER. I'll be waiting.$"

DewfordTown_Text_BrineyLandedInDewford:
	.string "MR. BRINEY: Ahoy!\n"
	.string "We've hit land in DEWFORD!\p"
	.string "You just go on and tell me whenever\n"
	.string "you want to set sail again!$"

DewfordTown_Text_WhereAreWeBound:
	.string "MR. BRINEY: Ahoy!\n"
	.string "For you, I'll go out to sea anytime!\p"
	.string "Now, my friend, where are we bound?$"

DewfordTown_Text_PetalburgWereSettingSail:
	.string "MR. BRINEY: PETALBURG, is it?\p"
	.string "Anchors aweigh!\n"
	.string "PEEKO, we're setting sail, my darling!$"

DewfordTown_Text_SlateportWereSettingSail:
	.string "MR. BRINEY: SLATEPORT, is it?\p"
	.string "Anchors aweigh!\n"
	.string "PEEKO, we're setting sail, my darling!$"

DewfordTown_Text_JustTellMeWhenYouNeedToSetSail:
	.string "MR. BRINEY: You just tell me whenever\n"
	.string "you need to set sail again!$"

DewfordTown_Text_GettingItchToFish:
	.string "This is a renowned fishing spot.\n"
	.string "Are you getting the itch to fish?$"

DewfordTown_Text_GiveYouOneOfMyRods:
	.string "I hear you, and I like what\n"
	.string "you're saying!\p"
	.string "I'll give you one of my fishing RODS.$"

DewfordTown_Text_ThrowInFishingAdvice:
	.string "And, as an added bonus, I'll even throw\n"
	.string "in a little fishing advice!\p"
	.string "First, you want to face the water,\n"
	.string "then use the ROD.\p"
	.string "Focus your mind…\n"
	.string "If you get a bite, pull on the ROD.\p"
	.string "Sometimes you can snag something\n"
	.string "immediately, but with bigger catches,\l"
	.string "you need to time the pulls on your ROD\l"
	.string "to haul them in.$"

DewfordTown_Text_ThatsTooBadThen:
	.string "Oh, is that so?\n"
	.string "That's too bad, then.$"

DewfordTown_Text_HowsYourFishing:
	.string "Yo!\n"
	.string "How's your fishing?$"

DewfordTown_Text_GreatHaulInSomeBigOnes:
	.string "Is that right! That's great!\n"
	.string "Haul in some big ones!$"

DewfordTown_Text_FishingAdvice:
	.string "Oh, hey, don't get down on yourself!\n"
	.string "I'll give you a little fishing advice.\p"
	.string "First, you want to face the water,\n"
	.string "then use the ROD.\p"
	.string "Focus your mind…\n"
	.string "If you get a bite, pull the ROD.\p"
	.string "Sometimes you can snag something\n"
	.string "immediately, but with bigger catches,\l"
	.string "you need to time the pulls on your ROD\l"
	.string "to haul them in.$"

DewfordTown_Text_XIsTheBiggestHappeningThingRight:
	.string "I like what's hip, happening, and trendy.\n"
	.string "I'm always checking it out.\p"
	.string "Listen, have you heard about this new\n"
	.string "“{STR_VAR_1}”?\p"
	.string "That's right!\n"
	.string "Of course you know!\p"
	.string "I mean, sheesh,\n"
	.string "“{STR_VAR_1}”…\l"
	.string "It's the hottest thing in cool!\p"
	.string "Wherever you're from,\n"
	.string "“{STR_VAR_1}”\l"
	.string "is the biggest happening thing, right?$"

DewfordTown_Text_TellMeWhatsNewAndIn:
	.string "Hunh?\n"
	.string "It's not the hip and happening thing?\p"
	.string "Well, hey, you have to tell me,\n"
	.string "what's new and what's “in”?$"

DewfordTown_Text_OfCourseIKnowAboutThat:
	.string "Hunh?\n"
	.string "“{STR_VAR_2}”?\p"
	.string "… …\p"
	.string "…Uh… Yeah! That's right!\n"
	.string "Yeah, I knew that! Knew it all along!\p"
	.string "Of course I know about that!\n"
	.string "“{STR_VAR_2},” right?\p"
	.string "Yeah, that's it, it's there!\n"
	.string "Isn't “{STR_VAR_2}”\l"
	.string "the coolest, or what?\p"
	.string "It's the hippest thing in hip.\n"
	.string "You think I'd not know about it?\p"
	.string "“{STR_VAR_1}”…\n"
	.string "It's, like, so five minutes ago.\p"
	.string "Now, “{STR_VAR_2}” is\n"
	.string "what's vital and in tune with the times!$"

DewfordTown_Text_XHuhIThinkYIsCool:
	.string "Hmm…\n"
	.string "“{STR_VAR_2},” huh?\p"
	.string "But personally, I think\n"
	.string "“{STR_VAR_1}”\l"
	.string "is what's real in cool.$"

DewfordTown_Text_HearOfAnyTrendsComeShareWithMe:
	.string "Well, if you hear of any happening new\n"
	.string "trends, come share them with me, okay?$"

DewfordTown_Text_YeahDefinitionOfInRightNow:
	.string "Yeah, absolutely right!\p"
	.string "“{STR_VAR_1}” is the\n"
	.string "definition of “in” right now.$"

Dewford_Text_XavierBuyMagikarpForJust500::
    .string "SALESMAN: Ho there, laddie!\n"
    .string "Have I got a deal just for you!\p"
    .string "I'll sell you a super-special POKéMON\n"
    .string "- a MAGIKARP - for just ¥500!\p"
    .string "So, you'll buy it, am I right? Y'know…\n"
    .string "they say that MAGIKARP evolves into\l"
    .string "a ferocious dragon!$"

Dewford_Text_HailanBuyMagikarpForJust500::
    .string "SALESMAN: Ho there, lassie!\n"
    .string "Have I got a deal just for you!\p"
    .string "I'll sell you a super-special POKéMON\n"
    .string "- a MAGIKARP - for just ¥500!\p"
    .string "So, you'll buy it, am I right? Y'know…\n"
    .string "they say that MAGIKARP evolves into\l"
    .string "a ferocious dragon!$"

DewfordTown_Text_MagikarpConfirm::
    .string "Buy a MAGIKARP for ¥500?$"

DewfordTown_Text_ReceivedMagikarp::
    .string "{PLAYER} received MAGIKARP!$"

DewfordTown_Text_MagikarpPurchased::
    .string "SALESMAN: A fine purchase!\n"
    .string "Take good care of that MAGIKARP!$"

DewfordTown_Text_MagikarpDeclined::
    .string "SALESMAN: You're missing out on\n"
    .string "the deal of a lifetime!$"

DewfordTown_Text_MagikarpNoMoney::
    .string "SALESMAN: You haven't got ¥500!\n"
    .string "Come back when you've got the cash!$"

DewfordTown_Text_MagikarpNoRoom::
    .string "SALESMAN: Looks like you can't\n"
    .string "take another POKéMON right now!$"

DewfordTown_Text_MagikarpAlreadyBought::
    .string "SALESMAN: How's that MAGIKARP?\n"
    .string "A real bargain, wasn't it?$"

DewfordTown_EventScript_Brawly::
    lock
    faceplayer
    goto_if_set FLAG_RECEIVED_HM_SURF, DewfordTown_EventScript_BrawlyAfterSurf

    specialvar VAR_RESULT, CalculatePlayerPartyCount
    goto_if_eq VAR_RESULT, 0, DewfordTown_EventScript_BrawlyNoPokemon

    goto_if_unset FLAG_DEWFORD_BRAWLY_INTRO_SEEN, DewfordTown_EventScript_BrawlyFirstMeetingWithPokemon
    goto DewfordTown_EventScript_BrawlyGiveSurf

DewfordTown_EventScript_BrawlyNoPokemon::
    goto_if_set FLAG_DEWFORD_BRAWLY_INTRO_SEEN, DewfordTown_EventScript_BrawlyReminder
    msgbox DewfordTown_Text_BrawlyIntro, MSGBOX_DEFAULT
    setflag FLAG_DEWFORD_BRAWLY_INTRO_SEEN
    release
    end

DewfordTown_EventScript_BrawlyFirstMeetingWithPokemon::
    msgbox DewfordTown_Text_BrawlyFirstMeetingWithPokemon, MSGBOX_DEFAULT
    setflag FLAG_DEWFORD_BRAWLY_INTRO_SEEN
    goto DewfordTown_EventScript_BrawlyGiveSurfItem

DewfordTown_EventScript_BrawlyReminder::
    msgbox DewfordTown_Text_BrawlyReminder, MSGBOX_DEFAULT
    release
    end

DewfordTown_EventScript_BrawlyGiveSurf::
    msgbox DewfordTown_Text_BrawlyFoundPokemon, MSGBOX_DEFAULT

DewfordTown_EventScript_BrawlyGiveSurfItem::
    giveitem ITEM_HM_SURF
    goto_if_eq VAR_RESULT, FALSE, DewfordTown_EventScript_BrawlyBagFull
    setflag FLAG_RECEIVED_HM_SURF
	setflag FLAG_CAN_USE_SURF
    msgbox DewfordTown_Text_BrawlyExplainHM, MSGBOX_DEFAULT
    release
    end

DewfordTown_EventScript_BrawlyBagFull::
    msgbox DewfordTown_Text_BrawlyBagFull, MSGBOX_DEFAULT
    release
    end

DewfordTown_EventScript_BrawlyAfterSurf::
    msgbox DewfordTown_Text_BrawlyRetired, MSGBOX_DEFAULT
    release
    end

DewfordTown_Text_BrawlyIntro:
    .string "BRAWLY: Hey, how's it hanging?\p"
    .string "I see you've somewhat got your\n"
    .string "bearings.\p"
    .string "If you wanna leave DEWFORD,\n"
    .string "I can help you out by giving you\l"
    .string "a special item that'll let you\l"
    .string "traverse the seas.\p"
    .string "But it's sort-of impossible to use\n"
    .string "without first owning a POKéMON\l"
    .string "that can swim in the water.\p"
    .string "Tell you what: go catch yourself\n"
    .string "a 'mon, and I'll give the item\l"
    .string "to you.$"

DewfordTown_Text_BrawlyReminder:
    .string "BRAWLY: Go grab a POKéMON, and show\n"
    .string "it to me.\p"
    .string "I'll give you an item that'll\n"
    .string "let you traverse the seas!$"

DewfordTown_Text_BrawlyFoundPokemon:
    .string "BRAWLY: Ah, there it is!\n"
    .string "You're a natural at this catching\l"
    .string "thing.\p"
    .string "Well, I'll hold up my end of the\n"
    .string "bargain, then. Here you go!$"

DewfordTown_Text_BrawlyFirstMeetingWithPokemon:
    .string "BRAWLY: Ah! I see you're getting\n"
    .string "your bearings just fine.\p"
    .string "And you've even caught a POKéMON\n"
    .string "to boot!\p"
    .string "Righteous stuff, buddy.\p"
    .string "In that case, lemme give you\n"
    .string "this special item.\p"
    .string "It'll help you traverse the seas.$"

DewfordTown_Text_BrawlyExplainHM:
    .string "BRAWLY: That's called an HM. Open up\n"
    .string "your BAG, and USE it on a POKéMON to\l"
    .string "teach them a special move.\p"
    .string "Oh, uh... Moves are kinda like spells\n"
    .string "that your POKéMON can cast to fight\l"
    .string "in battle.\p"
    .string "But in the case of HMs, a move like\n"
    .string "SURF can also be used outside of\l"
    .string "battle!\p"
    .string "Go up to any body of water and press A\n"
    .string "once you've got a POKéMON that knows\l"
	.string "SURF. You'll see what I mean.$"

DewfordTown_Text_BrawlyBagFull:
    .string "Whoa, your BAG is full!\p"
    .string "Make some room and come back. I've\n"
    .string "still got your special item!$"

DewfordTown_Text_BrawlyRetired:
    .string "BRAWLY: Y'know... I used to be\n"
    .string "somewhat of a famous fighter.\p"
    .string "That was back in the days of the\n"
    .string "POKéMON LEAGUE.\p"
    .string "Now that the economy has gotten so\n"
    .string "bad, and the POKéMON LEAGUE is gone,\l"
    .string "I had to close my GYM. Sad times.$"
