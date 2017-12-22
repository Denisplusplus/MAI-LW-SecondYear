#ifdef TLIST_H

template <typename Q, typename O> TNList<Q, O>::TNList()
{
    head = std::make_shared<Node>(Node());
    count = 0;
}

template <typename Q, typename O> TNList<Q, O>::Node::Node()
{
    next = nullptr;
    itemsInNode = 0;
}

template <typename Q, typename O> TNList<Q, O>::Node::Node(const O& item)
{
    data.PushFront(item);
    itemsInNode = 1;
}

template <typename Q, typename O> void TNList<Q, O>::removeByType(const int& type)
{
    auto tmp = head;
    while(tmp) {
        if (tmp->itemsInNode) {
            for (int i = 0; i < 5; ++i) {
                auto iter = tmp->data.begin();

                for (int k = 0; k < tmp->data.GetLength(); ++k) {
                    if (iter->Type() == type) {
                        tmp->data.Pop(k + 1);
                        tmp->itemsInNode--;
                        break;
                    }
                    ++iter;
                }
            }
        }
        tmp = tmp->next;
    }
}

template <typename Q, typename O> void TNList<Q, O>::push(const O& item)
{
    auto tmp = this->head;
    while(tmp->next) {
    	tmp = tmp->next;
    }
    if (tmp->itemsInNode < 5) {
        tmp->data.PushFront(item);
        tmp->itemsInNode++;
    } else {
        auto newNode = std::make_shared<Node>(Node(item));
        tmp->next = newNode;
        ++count;
    }
}


template <typename Q, typename O> void TNList<Q, O>::print()
{
    auto tmp = head;
    while (tmp) {
        if (tmp->itemsInNode) {
            tmp->data.sort();
            for (const auto &i: tmp->data) {
                i->Print();
            }
            std::cout << std::endl;
        }
        tmp = tmp->next;
    }
}


template <typename Q, typename O> void TNList<Q, O>::removeLesser(const double& sqr)
{
    auto tmp = head;
    while(tmp) {
        if (tmp->itemsInNode) {
            for (int i = 0; i < 5; ++i) {
                auto iter = tmp->data.begin();

                for (int k = 0; k < tmp->data.GetLength(); ++k) {
                    if (iter->Square() < sqr) {
                        tmp->data.Pop(k + 1);
                        tmp->itemsInNode--;
                        break;
                    }
                    ++iter;
                }
            }
        }
        tmp = tmp->next;
    }
}

#endif