/*	Herb heal by silencer@fy4.

compared it with normal healing pills
1. 5 silver ��Ƥ��ҩ 					20 sen
2. 20 silver ���ϰ�ҩ������裬������ 			100kee/50sen/50gin
3. 60 silver ����/�˲�/¹��  				300kee/200gin/200sen
4. 100 silver	��ɫ��绨/��Ҷ��β��/ѩ֥  		1500kee/1000sen/1000gin
5. 200 silver	�Ż���¶��/�����ܵ���/���令�ĵ�	5000kee/2500sen/2500gin


all can be collected by knight player.

L 100 herb, can be bought
type 1: herb_a: "������","�Ⱦ���","��Ǯ��","�ض���","���Ĳ�", 	Level 100,  base_value 0.3-0.8g,    effect 500-2500 kee
type 2: herb_b: " "ľ��","��ľ��","̴��",			Level 100, base_value 0.5-0.7g      effect 500-1000-2000 sen/gin

L Level 150 herb random_drop 
type 1: herb_c: "�����Ĳ�","�Ϻӳ�","��Ҷ��צ��",  random(3) drop, knight 3000, 3500, 4000 kee
type 5: herb_d: "�׻��߲�","���ĺ���","���Ҷ",    poison self-made weapon..... 
type 4  herb_e: "������"	depoison

L 200 herb
type 3: herb_f: "��֥","����Ҷ"	random drop    4000/2000/2000 cure poison, heal both value.

So the parameters are
Level: requirement for herb level
field:  kee/gin(sen)/full/depoison/poison
effect: amount that it heals

*/

inherit MEDICINE;
#include <ansi.h>

void create()
{
	set_name("����",({"yincao", "herb"}));
        if( clonep() )
                set_default_object(__FILE__);
	else {
	    set("long",(: herb_desc :));
	    set("unit","��");
	    set("base_unit","��");
	    set("base_weight",30);
	    set("material","herb");
	    
	    set("usage_type","herb");
	    set("heal_type","kee/10");
	    set("type","full");
	    set("base_value",0);
	    set("level",150);
	    set("effect",5000);
	    set("field","kee");
	    set("volumn",1);
	}
	set_amount(1);
}
