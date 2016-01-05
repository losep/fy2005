#include <ansi.h>
inherit NPC;
void use_poison();

void create()
{
        set_name(HIC"��������"NOR, ({ "deadly bat", "bat" }) );
        set("race", "����");
        set("age", 4);
        set("long", "һֻ�ǳ����µ���������\n");

        set("attitude", "aggressive");
        set_skill("dodge", 500+random(150));
        
        set("arrive_msg", "һ������طɹ���");
        set("leave_msg", "һ������طɿ���");
        set("combat_exp", 600000+random(400000));
		set("bellicosity", 3000 );
        set("chat_chance_combat", 10);
        set("chat_msg_combat", ({
                (: use_poison :),
        }) );
        set("chat_chance", 20);
        set("chat_msg", ({
                (: random_move :),
        }) );

        setup();
}

void use_poison()
{
        object *enemy, ob;
        string msg;

        enemy = query_enemy();
        if( sizeof(enemy) ) ob = enemy[random(sizeof(enemy))];
		tell_object(ob,"Ѫ�����͵س�������һ��ҧ����Ĳ����ϣ������һ���ʹ��������\n");
        ob->apply_condition("bat_poison",this_player()->query_condition("bat_poison")+ random(3)+20);
        return;
}


void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) ) {
                kill_ob(ob);
        }
}
